#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include <omnetpp.h>
#include "BaseStation.h"
#include "Packet_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Aircraft : public cSimpleModule {
    private:
        double v = 0.2639; // Velocity of the aircraft (950 km/h)
        double h = 11.8; // Altitude of the aircraft (km)

        //The geographical stating point of the aircraft in the Area
        double x_arrival;
        double y_arrival;

        //The geographical leaving point of the aircraft in the Area
        double x_departure;
        double y_departure;

        // The Base Station connected to the Aircraft. The Aircraft changes BS each t s.
        cModule *BS_connect;

        // The packet that the Aircraft sends periodically (each k s)
        Packet *packet;

        // Events
        cMessage *event_t;
        cMessage *event_k;
    protected:
        virtual void initialize();
        virtual bool connectionBS();
        virtual void distanceBS();
        virtual void generatePacket();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();
};

#endif /* AIRCRAFT_H_ */
