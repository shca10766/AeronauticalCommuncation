#include "AircraftGenerator.h"
#include "Aircraft.h"

Define_Module(AircraftGenerator);

void AircraftGenerator::initialize() {
    aircraftCounter = 0;
    WATCH(aircraftCounter);

    // schedule the first message timer for start time
    scheduleAt(par("startTime"), new cMessage("newACTimer"));
}

void AircraftGenerator::handleMessage(cMessage *msg) {
    ASSERT(msg->isSelfMessage());
    int nbAircraft = par("nbAircraft");
    omnetpp::SimTime stopTime = par("stopTime");
        if ((nbAircraft < 0 || nbAircraft > aircraftCounter) && (stopTime < 0 || stopTime > simTime())) {
            // reschedule the timer for the next message
            scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);

            //find factory Aircraft
            cModuleType *aicraftType = cModuleType::get("aeronauticalcommunication.Aircraft");

            //create Aircraft module
            aircraftCounter++;
            char nbAircraft_string[64];
            sprintf(nbAircraft_string, "AC%d", nbAircraft);
            const char * aircraftName = nbAircraft_string;
            cModule *aircraft = aicraftType->create(aircraftName, this->getParentModule());
            aircraft->finalizeParameters();
            aircraft->buildInside();

            //create activation message
            aircraft->scheduleStart(simTime());
        }
        else {
            // finished
            delete msg;
        }
}

