#include "Aircraft.h"
#include "BaseStation.h"
#include "Packet_m.h"

Define_Module(Aircraft);

void Aircraft::initialize() {
    double random_init = uniform(0,1);
    double random_arrival = uniform(0,200);

    double random_finish = uniform(0,0.9);
    double random_departure = uniform(0,200);

    if (random_init < 0.25) {
        x_arrival = 0;
        y_arrival = random_arrival;

        if (random_finish < 0.3) {
            x_departure = 200;
            y_departure = random_departure;
        }
        else if (random_finish >= 0.3 && random_finish < 0.6) {
            y_departure = 0;
            x_departure = random_departure;
        }
        else {
            y_departure = 200;
            x_departure = random_departure;
        }
    }
    else if (random_init >= 0.25 && random_init < 0.5 ) {
        x_arrival = 200;
        y_arrival = random_arrival;

        if (random_finish < 0.3) {
            x_departure = 0;
            y_departure = random_departure;
        }
        else if (random_finish >= 0.3 && random_finish < 0.6) {
            y_departure = 0;
            x_departure = random_departure;
        }
        else {
            y_departure = 200;
            x_departure = random_departure;
        }
    }
    else if (random_init >= 0.5 && random_init < 0.75 ) {
        y_arrival = 0;
        x_arrival = random_arrival;

        if (random_finish < 0.3) {
            x_departure = 0;
            y_departure = random_departure;
        }
        else if (random_finish >= 0.3 && random_finish < 0.6) {
            x_departure = 200;
            y_departure = random_departure;
        }
        else {
            y_departure = 200;
            x_departure = random_departure;
        }
    }
    else {
        y_arrival = 200;
        x_arrival = random_arrival;

        if (random_finish < 0.3) {
            x_departure = 0;
            y_departure = random_departure;
        }
        else if (random_finish >= 0.3 && random_finish < 0.6) {
            x_departure = 200;
            y_departure = random_departure;
        }
        else {
            y_departure = 0;
            x_departure = random_departure;
        }
    }

    connectionBS();

    //event = new cMessage("event");
    //packet = new Packet();

    //scheduleAt(par("arrival_time") + par("k").doubleValue(), event);
    //send(packet, "out");
}


void Aircraft::handleMessage(cMessage *msg) {

}

void Aircraft::connectionBS() {
    double a = (x_departure - x_arrival)/(y_departure - y_arrival);
    double x = (v*simTime().dbl()*a)/(sqrt(1+a*a)) + x_arrival;
    double y = y_arrival + (v*simTime().dbl())/(sqrt(1+a*a));

    if (x < 100 && y >= 100) {
        BS_connect = getParentModule() -> getSubmodule("baseStation1");
    }
    else if (x >= 100 && y >= 100) {
        BS_connect = getParentModule() -> getSubmodule("baseStation2");
    }
    else if (x < 100 && y < 100) {
        BS_connect = getParentModule() -> getSubmodule("baseStation3");
    }
    else {
        BS_connect = getParentModule() -> getSubmodule("baseStation4");
    }
}

void Aircraft::generatePacket() {
    packet = new Packet("packet");

    packet -> setId_aircraft(par("id"));
    packet -> setId_baseStation(BS_connect -> par("nBS").intValue());

    distanceBS();
}

void Aircraft::distanceBS() {
    double a = (x_departure - x_arrival)/(y_departure - y_arrival);
    double x = (v*simTime().dbl()*a)/(sqrt(1+a*a)) + x_arrival;
    double y = y_arrival + (v*simTime().dbl())/(sqrt(1+a*a));

    int xBS = BS_connect -> par("x_BS").intValue();
    int yBS = BS_connect -> par("y_BS").intValue();

    double d = sqrt(pow(xBS-x, 2) + pow(yBS-y, 2) + h*h);

    packet -> setX_aircraft(x);
    packet -> setY_aircraft(y);
    packet -> setDistance_AC_BS(d);
}
