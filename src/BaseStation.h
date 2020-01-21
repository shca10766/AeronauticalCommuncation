#ifndef BASESTATION_H_
#define BASESTATION_H_

#include <omnetpp.h>
#include "Packet_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class BaseStation : public cSimpleModule {
    private:
    protected:
        virtual void initialize();
        virtual void hanfleMessage(cMessage *msg);
        virtual void finish();
};

#endif /* BASESTATION_H_ */
