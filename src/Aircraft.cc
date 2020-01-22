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

    // We connect to the first time to a BS
    connectionBS();

    // We generate the first packet
    generatePacket();
    send(packet, "out");

    // k periodicity : we send a packet to the BS each k seconds
    event_k = new cMessage("event_k");
    scheduleAt(simTime()+par("k").doubleValue(),event_k);

    // t periodicity : we do a handover operation each t seconds
    event_t = new cMessage("event_t");
    scheduleAt(simTime()+par("t").doubleValue(),event_t);
}


void Aircraft::handleMessage(cMessage *msg) {
    // When the Aircraft receives a message for an handover operation
    if(msg == "event_t") {
        // We connect the Aircraft to the nearest BS
        if(connectionBS()){
            // creation of a self-message event_t
            cMessage *event_t = new cMessage("event_t");
            // the self-message is scheduled to be sent after t seconds
            scheduleAt(simTime()+par("t").doubleValue(),event_t);
            delete event_t;
        // The Aircraft is not in the Area anymore
        }else{
            // destruction of the Aircraft module
            //this->callFinish();
            this->deleteModule();
        }
    }
    // When the Aircraft receives a message for sending a packet to the BS
    else {
        // creation of a self-message event_k
        cMessage *event_k = new Message("event_k");
        // the self-message is scheduled to be sent after k seconds
        scheduleAt(simTime()+par("k").doubleValue(),event_k);
        // A/C generates a packet for BS
        generatePacket();
        send(packet, "out");
        packet = nullptr;
        delete event_k;
    }

}

bool Aircraft::connectionBS() {
    // we compute the slope of the Aircraft trajectory
    double a = (x_departure - x_arrival)/(y_departure - y_arrival);
    // we compute the x coordinate of the Aircraft, using the slope, the simTime, the velocity and the x_arrival
    double x = (v*simTime().dbl()*a)/(sqrt(1+a*a)) + x_arrival;
    // we compute the y coordinate of the Aircraft, using the slope, the simTime and the velocity and the y_arrival
    double y = y_arrival + (v*simTime().dbl())/(sqrt(1+a*a));

    // when the aircraft is outside the Area
    if (x < 0 || y < 0 || x > 200 || y > 200){
        return false;
    }
    // when the aircraft is inside the Area
    else{
        if (x < 100 && y >= 100) { // when the aircraft is on the BS1 area
            BS_connect = getParentModule() -> getSubmodule("baseStation1");
        }
        else if (x >= 100 && y >= 100) {// when the aircraft is on the BS2 area
            BS_connect = getParentModule() -> getSubmodule("baseStation2");
        }
        else if (x < 100 && y < 100) {// when the aircraft is on the BS3 area
            BS_connect = getParentModule() -> getSubmodule("baseStation3");
        }
        else {// when the aircraft is on the BS4 area
            BS_connect = getParentModule() -> getSubmodule("baseStation4");
        }
        return true;
    }
}

void Aircraft::generatePacket() {
    // create a packet to be send
    packet = new Packet("packet");

    // write the id of the Aicraft and the BaseStation in the packet
    packet -> setId_aircraft(par("id"));
    packet -> setId_baseStation(BS_connect -> par("nBS").intValue());

    // compute the distance d between BS and A/C and retrieve A/C's coordinates
    distanceBS();
}

void Aircraft::distanceBS() {
    // we compute the slope of the Aircraft trajectory
    double a = (x_departure - x_arrival)/(y_departure - y_arrival);
    // we compute the x coordinate of the Aircraft, using the slope, the simTime, the velocity and the x_arrival
    double x = (v*simTime().dbl()*a)/(sqrt(1+a*a)) + x_arrival;
    // we compute the y coordinate of the Aircraft, using the slope, the simTime and the velocity and the y_arrival
    double y = y_arrival + (v*simTime().dbl())/(sqrt(1+a*a));

    // we retrieve the BS's coordinates
    int xBS = BS_connect -> par("x_BS").intValue();
    int yBS = BS_connect -> par("y_BS").intValue();

    // we compute the distance between BS and the aircraft using the aircraft's coordinates, the BS's coordinates and the altitude of the aircraft h
    double d = sqrt(pow(xBS-x, 2) + pow(yBS-y, 2) + h*h);

    // set the coordinates of the aircraft and the distance between the aircraft and the BS in the packet
    packet -> setX_aircraft(x);
    packet -> setY_aircraft(y);
    packet -> setDistance_AC_BS(d);
}
