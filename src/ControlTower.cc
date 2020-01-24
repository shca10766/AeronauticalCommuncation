#include "ControlTower.h"
#include "Packet_m.h"

Define_Module(ControlTower);

void ControlTower::initialize()
{
    endToEndDelayB1Signal = registerSignal("endToEndDelayB1");
    endToEndDelayB2Signal = registerSignal("endToEndDelayB2");
    endToEndDelayB3Signal = registerSignal("endToEndDelayB3");
    endToEndDelayB4Signal = registerSignal("endToEndDelayB4");
    serviceTimeSignal = registerSignal("serviceTime");
}

void ControlTower::handleMessage(cMessage *msg)
{
    Packet *packet = check_and_cast<Packet *>(msg);
    const char* nom_module = msg -> getSenderModule() -> getName();

    // gather statistics - end-to-end delay
    // from B1
    if(strcmp("baseStation1", nom_module ) == 0) {
        emit(endToEndDelayB1Signal, simTime() - packet -> getCreationTime());
        EV << "BS1\n";
    }
    // from B2
    else if(strcmp("baseStation2", nom_module ) == 0) {
        emit(endToEndDelayB2Signal, simTime() - packet -> getCreationTime());
        EV << "BS2\n";
    }
    // from B3
    else if(strcmp("baseStation3", nom_module ) == 0) {
        emit(endToEndDelayB3Signal, simTime() - packet -> getCreationTime());
        EV << "BS3\n";
    }
    //from B4
    else if(strcmp("baseStation4", nom_module ) == 0) {
        emit(endToEndDelayB4Signal, simTime() - packet -> getCreationTime());
        EV << "BS4\n";
    }

    // service time - to get the mean of Scenario 1 and use it in Scenario 2
    emit(serviceTimeSignal, packet -> getServiceTime());

    delete msg;
}

void ControlTower::finish()
{

}
