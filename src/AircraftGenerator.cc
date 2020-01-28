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
    ASSERT(msg -> isSelfMessage());
    int nbAircraft = par("nbAircraft");
    double stopTime = par("stopTime");
    if ((nbAircraft < 0 || nbAircraft > aircraftCounter) && (stopTime < 0 || stopTime > simTime().dbl())) {
        // reschedule the timer for the next message
        scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);

        // find factory Aircraft
        cModuleType *aicraftType = cModuleType::get("aeronauticalcommunication.Aircraft");

        // create Aircraft module
        aircraftCounter++;
        char nbAircraft_string[255];
        sprintf(nbAircraft_string, "AC%d", aircraftCounter);
        const char * aircraftName = nbAircraft_string;
        cModule *aircraft = aicraftType->create(aircraftName, this->getParentModule());

        // set up parameter "id"
        aircraft -> par("id") = aircraftCounter;
        double time = simTime().dbl();
        aircraft -> par("startTime") = time;
        aircraft -> finalizeParameters();
        aircraft -> buildInside();

        // create activation message
        aircraft-> scheduleStart(simTime());
        aircraft -> callInitialize();
    }
    else {
        // finished
        delete msg;
    }
}

