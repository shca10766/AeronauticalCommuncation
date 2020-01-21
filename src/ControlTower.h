#ifndef CONTROLTOWER_H_
#define CONTROLTOWER_H_

#include <omnetpp.h>
#include "Packet_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class ControlTower : public cSimpleModule {
    private:
    protected:
        virtual void initialize();
        virtual void hanfleMessage(cMessage *msg);
        virtual void finish();
};


#endif /* CONTROLTOWER_H_ */
