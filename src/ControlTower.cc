#include "ControlTower.h"
#include "Packet_m.h"

Define_Module(ControlTower);

void ControlTower::initialize()
{
    endToEndDelaySignal = registerSignal("endToEndDelay");
    serviceTimeSignal = registerSignal("serviceTime");
}

void ControlTower::handleMessage(cMessage *msg)
{
    Packet *packet = check_and_cast<Packet *>(msg);

    // gather statistics
    emit(endToEndDelaySignal, simTime() - packet -> getCreationTime());
    emit(serviceTimeSignal, packet -> getServiceTime());

    delete msg;
}

void ControlTower::finish()
{

}
