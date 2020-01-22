#ifndef AIRCRAFTGENERATOR_H_
#define AIRCRAFTGENERATOR_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class AircraftGenerator : public cSimpleModule {
    private:
        int aircraftCounter;
        std::string aircraftName;
        simsignal_t createdSignal;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif /* AIRCRAFTGENERATOR_H_ */
