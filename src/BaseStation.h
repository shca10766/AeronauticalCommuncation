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
        // signals
        simsignal_t droppedSignal;
        simsignal_t queueLengthSignal;
        simsignal_t queueingTimeSignal;
        simsignal_t busySignal;

        Packet *packetServiced;
        cMessage *endServiceMsg;
        cQueue queue;

        // characteristics
        int capacity;
        bool fifo;

        //
        Packet *getFromQueue();

    public:
        BaseStation();
        virtual ~BaseStation();
        int length();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;
        virtual void finish() override;

        // behavior
        virtual void arrival(Packet *packet);
        virtual simtime_t startService(Packet *packet);
        virtual void endService(Packet *packet);
};

#endif /* BASESTATION_H_ */
