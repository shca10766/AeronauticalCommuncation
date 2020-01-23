#include "ControlTower.h"
#include "Packet_m.h"

Define_Module(ControlTower);

void ControlTower::initialize()
{
    endToEndDelaySignal = registerSignal("endToEndDelay");
}

void ControlTower::handleMessage(cMessage *msg)
{
    Packet *packet = check_and_cast<Packet *>(msg);

    // gather statistics
    emit(endToEndDelaySignal, simTime() - packet -> getCreationTime());

    delete msg;
}

void ControlTower::finish()
{

}
