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
        // Signals for statistics
        simsignal_t endToEndDelaySignal;
        simsignal_t serviceTimeSignal;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
};


#endif /* CONTROLTOWER_H_ */
