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
        simsignal_t endToEndDelayBSsSignal;
        simsignal_t endToEndDelayB1Signal;
        simsignal_t endToEndDelayB2Signal;
        simsignal_t endToEndDelayB3Signal;
        simsignal_t endToEndDelayB4Signal;
        simsignal_t serviceTimeSignal;
        simsignal_t interKTimeSignal;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
};


#endif /* CONTROLTOWER_H_ */
