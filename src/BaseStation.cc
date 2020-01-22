#include "BaseStation.h"
#include "Packet_m.h"

Define_Module(BaseStation);

BaseStation::Basestation()
{
    packetServiced = nullptr;
    endServiceMsg = nullptr;
}

BaseStation::~BaseStation()
{
    delete packetServiced;
    cancelAndDelete(endServiceMsg);
}

void BaseStation::initialize()
{
    // Statistics (signals)
    droppedSignal = registerSignal("dropped");
    queueingTimeSignal = registerSignal("queueingTime");
    queueLengthSignal = registerSignal("queueLength");
    emit(queueLengthSignal, 0);
    busySignal = registerSignal("busy");
    emit(busySignal, false);

    // Parameters of the queue of BS
    endServiceMsg = new cMessage("end-service");
    fifo = par("fifo");
    capacity = par("capacity");
    queue.setName("queue");
}

void BaseStation::handleMessage(cMessage *msg)
{
    // When the server finishes to process a packet
    if (msg == endServiceMsg) {
        endService(packetServiced);
        // when the queue is empty : we don't have another packet to process
        if (queue.isEmpty()) {
            packetServiced = nullptr;
            emit(busySignal, false); // the queue is not busy anymore
        }
        // when the queue is not empty (at least one packet)
        else {
            // we get the packet from the queue to process it
            packetServiced = getFromQueue();
            emit(queueLengthSignal, length());
            // we start counting the service time for the packet
            simtime_t serviceTime = startService(packetServiced);
            // we schedule a endServiceMsg after the service time
            scheduleAt(simTime()+serviceTime, endServiceMsg);
        }
    }
    else {
        //a packet arrives to the BS from an Aircraft
        Packet *packet = check_and_cast<Packet *>(msg);
        arrival(packet);

        if (!packetServiced) {
            // processor was idle
            packetServiced = packet;
            emit(busySignal, true);
            // we start counting the service time for the packet
            simtime_t serviceTime = startService(packetServiced);
            // we schedule a endServiceMsg after the service time
            scheduleAt(simTime()+serviceTime, endServiceMsg);
        }
        else {
            // we insert the packet in the queue since it cannot be processed for now
            queue.insert(packet);
            emit(queueLengthSignal, length());
            packet->setQueueCount(packet->getQueueCount() + 1);
        }
    }
}

void BaseStation::refreshDisplay() const
{
    getDisplayString().setTagArg("i2", 0, packetServiced ? "status/execute" : "");
    getDisplayString().setTagArg("i", 1, queue.isEmpty() ? "" : "green");
}

Packet *BaseStation::getFromQueue()
{
    Packet *packet;
    packet = (Packet *)queue.pop();
    return packet;
}

int BaseStation::length()
{
    return queue.getLength();
}

void BaseStation::arrival(Packet *packet)
{
    packet->setTimestamp();
}

simtime_t BaseStation::startService(Packet *packet)
{
    // gather queueing time statistics
    simtime_t d = simTime() - packet->getTimestamp();
    emit(queueingTimeSignal, d);
    packet->setTotalQueueingTime(packet->getTotalQueueingTime() + d);
    EV << "Starting service of " << packet->getName() << endl;
    packet->setTimestamp();
    // s = T.d², T = 0.03
    par("serviceTime").setDoubleValue(0.03*pow(packet->par("d").doubleValue(),2));
    return par("serviceTime").doubleValue();
}

void BaseStation::endService(packet *packet)
{
    EV << "Finishing service of " << packet->getName() << endl;
    simtime_t d = simTime() - packet->getTimestamp();
    packet->setTotalServiceTime(packet->getTotalServiceTime() + d);
    send(packet, "out");
}

void BaseStation::finish()
{
}
