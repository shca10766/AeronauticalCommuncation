#include "BaseStation.h"
#include "Packet_m.h"

Define_Module(BaseStation);

BaseStation::BaseStation()
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
    queueLengthSignal = registerSignal("queueLength");
    serviceTimeSignal = registerSignal("serviceTime");
    emit(queueLengthSignal, 0);

    // Parameters of the queue of BS
    endServiceMsg = new cMessage("end-service");
    fifo = par("fifo");
    capacity = par("capacity");
    queue.setName("queue");
}

void BaseStation::handleMessage(cMessage *msg)
{
    // When the server finishes to service a packet
    if (msg == endServiceMsg) {
        endService(packetServiced);
        // when the queue is empty : we don't have another packet to service
        if (queue.isEmpty()) {
            packetServiced = nullptr;
        }
        // when the queue is not empty (at least one packet)
        else {
            // we get the packet from the queue to service it
            packetServiced = getFromQueue();
            emit(queueLengthSignal, length()); //queue length statistics
            // we start counting the service time for the packet
            simtime_t serviceTime = startService(packetServiced);
            // we schedule a endServiceMsg after the service time
            scheduleAt(simTime()+serviceTime, endServiceMsg);
        }
    }
    //When a packet arrives to the BS from an Aircraft
    else {
        Packet *packet = check_and_cast<Packet *>(msg);
        //We start to count the time of the packet in the Base Station
        arrival(packet);

        if (!packetServiced) {
            // processor was idle
            packetServiced = packet;
            // we start to count the service time for the packet
            simtime_t serviceTime = startService(packetServiced);
            // we schedule a endServiceMsg after the service time
            scheduleAt(simTime()+serviceTime, endServiceMsg);
        }
        else {
            // we insert the packet in the queue since it cannot be processed for now
            queue.insert(packet);
            emit(queueLengthSignal, length()); // queue length statistics
            packet->setQueueCount(packet->getQueueCount() + 1);
        }
    }
}

//We display the information about the queue state and the packet served on the Base Station
void BaseStation::refreshDisplay() const
{
    getDisplayString().setTagArg("i2", 0, packetServiced ? "status/execute" : "");
    getDisplayString().setTagArg("i", 1, queue.isEmpty() ? "" : "green");
}

// We take the next packet to be processed in the queue
Packet *BaseStation::getFromQueue()
{
    Packet *packet;
    packet = (Packet *)queue.pop();
    return packet;
}

// We retrieve the size of the queue
int BaseStation::length()
{
    return queue.getLength();
}

// We set the arrival time of the packet using the timestamp
void BaseStation::arrival(Packet *packet)
{
    packet->setTimestamp();
}

// We start the service time for the packet in the BaseStation
simtime_t BaseStation::startService(Packet *packet)
{
    EV << "Starting service of " << packet->getName();
    packet->setTimestamp();
    // s = T.d� = T.(dBCAC�+h�), T = 0.001
    double serviceTime;
    serviceTime = par("T").doubleValue()*(pow(packet->getDistance_AC_BS(),2)+139.24);
    EV << "\nService time : " << serviceTime << " s distance : " << packet->getDistance_AC_BS() << " km";
    packet->setServiceTime(serviceTime);
    emit(serviceTimeSignal, serviceTime);
    return serviceTime;
}

// We end the service time for the packet in the Base Station
void BaseStation::endService(Packet *packet)
{
    EV << "Finishing service of " << packet->getName();
    simtime_t d = simTime() - packet->getTimestamp();
    send(packet, "outBS");
}

void BaseStation::finish()
{

}
