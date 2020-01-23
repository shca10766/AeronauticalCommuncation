#include "ControlTower.h"
#include "Packet_m.h"

Define_Module(ControlTower);

void ControlTower::initialize()
{
    endToEndDelaySignal = registerSignal("endToEndDelay");
    totalServiceTimeSignal = registerSignal("totalServiceTime");
}

void ControlTower::handleMessage(cMessage *msg)
{
    Packet *packet = check_and_cast<Packet *>(msg);

    // gather statistics
    emit(endToEndDelaySignal, simTime()- packet->getCreationTime());
    emit(totalServiceTimeSignal, packet->getTotalServiceTime());

    delete msg;
}

void ControlTower::finish()
{

}
