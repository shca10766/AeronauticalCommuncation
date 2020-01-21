#ifndef ROUTING_H_
#define ROUTING_H_

#include <omnetpp.h>
#include "Packet_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Routing : public cSimpleModule {
    private:
    protected:
        virtual void initialize();
        virtual void hanfleMessage(cMessage *msg);
        virtual void finish();
};

#endif /* ROUTING_H_ */
