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

        double x_arrival;
        double y_arrival;

        double x_departure;
        double y_departure;

        cModule *BS_connect;

        Packet *packet;
    protected:
        virtual void initialize();
        virtual void connectionBS();
        virtual void distanceBS();
        virtual void generatePacket();
        virtual void handleMessage(cMessage *msg);
};

#endif /* AIRCRAFT_H_ */
