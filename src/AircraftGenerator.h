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
        int randomAC_generator = uniform(1,261);

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif /* AIRCRAFTGENERATOR_H_ */
