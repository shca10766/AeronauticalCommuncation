#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <omnetpp.h>
#include "Packet_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Aircraft : public cSimpleModule {
    private:
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

#endif /* AIRCRAFT_H_ */
