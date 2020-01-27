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
        simsignal_t queueLengthSignal;
        simsignal_t serviceTimeSignal;

        // serviced packet
        Packet *packetServiced;
        // message to inform that the server has finished to service a packet
        cMessage *endServiceMsg;
        // queue of the BS
        cQueue queue;

        // characteristics of the queue of the Bs
        int capacity;
        bool fifo;

        // packet in the queue
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
