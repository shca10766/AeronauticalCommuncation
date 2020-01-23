#include "Aircraft.h"
#include "BaseStation.h"
#include "Packet_m.h"

Define_Module(Aircraft);

void Aircraft::initialize() {
    packet = nullptr;
    event_t = nullptr;

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
    x = x_arrival;
    y = y_arrival;
    // We connect to the first time to a BS
    connectionBS(x_arrival, y_arrival);

    // We generate the first packet
    generatePacket();
    send(packet, "outAircraft");
    packet = nullptr;

    // k periodicity : we send a packet to the BS each k seconds
    event_k = new cMessage("event_k");
    scheduleAt(simTime().dbl() + par("k").doubleValue(), event_k);

    // t periodicity : we do a handover operation each t seconds
    event_t = new cMessage("event_t");
    scheduleAt(simTime().dbl() + par("t").doubleValue(), event_t);
}


void Aircraft::handleMessage(cMessage *msg) {
    // When the Aircraft receives a message for an handover operation
    getXPosition();
    getYPosition();
    if(msg == event_t) {
        // We connect the Aircraft to the nearest BS
        if(connectionBS(x,y)){
            // the self-message is scheduled to be sent after t seconds
            scheduleAt(simTime().dbl() + par("t").doubleValue(), event_t);
        // The Aircraft is not in the Area anymore
        }else{
            // destruction of the Aircraft module
            // this->callFinish();
            this -> deleteModule();
        }
    }

    // When the Aircraft receives a message for sending a packet to the BS
    else {
        // the self-message is scheduled to be sent after k seconds
        scheduleAt(simTime().dbl() + par("k").doubleValue(), event_k);
        // A/C generates a packet for BS
        generatePacket();
        send(packet, "outAircraft");
        packet = nullptr;
    }

}

bool Aircraft::connectionBS(double x, double y) {
    // when the aircraft is outside the Area
    if (x < 0 || y < 0 || x > 200 || y > 200){
        return false;
    }
    // when the aircraft is inside the Area
    else {
        cModule *new_BS_connect = nullptr;
        if (x < 100 && y >= 100) { // when the aircraft is on the BS3 area
            new_BS_connect = getParentModule() -> getSubmodule("baseStation3");
        }
        else if (x >= 100 && y >= 100) {// when the aircraft is on the BS4 area
            new_BS_connect = getParentModule() -> getSubmodule("baseStation4");
        }
        else if (x < 100 && y < 100) {// when the aircraft is on the BS1 area
            new_BS_connect = getParentModule() -> getSubmodule("baseStation1");
        }
        else {// when the aircraft is on the BS2 area
            new_BS_connect = getParentModule() -> getSubmodule("baseStation2");
        }
        if (new_BS_connect != BS_connect) {
            cGate * outAircraft = gate("outAircraft");

            if (BS_connect != nullptr) {
                outAircraft -> disconnect();
            }

            BS_connect = new_BS_connect;

            int sizeGate = BS_connect -> gateSize("inBS");
            int index = 0;
            cGate * inBS = nullptr;

            while(index < sizeGate && inBS == nullptr) {
                bool gatesConnected = BS_connect -> gate("inBS", index) -> isConnected();
                if (!gatesConnected) {
                    inBS = BS_connect -> gate("inBS", index);
                }
                index++;
            }

            if (index == sizeGate) {
                BS_connect -> setGateSize("inBS", sizeGate + 1);
                inBS = BS_connect -> gate("inBS", sizeGate);
            }
            outAircraft->connectTo(inBS);
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

    // We set the time where the packet leaves the A/C
    packet -> setCreationTime(simTime());
}

void Aircraft::distanceBS() {
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

void Aircraft::getXPosition() {
    // we compute the slope of the Aircraft trajectory
    double a = (x_departure - x_arrival)/(y_departure - y_arrival);
    // we compute the x coordinate of the Aircraft, using the slope, the simTime, the velocity and the x_arrival
    double difX = (v*(simTime().dbl() - par("startTime").doubleValue())*abs(a))/(sqrt(1+a*a));
    if (x_departure < x_arrival) { x = x_arrival - difX; }
    else { x = x_arrival + difX;}
}

void Aircraft::getYPosition() {
    // we compute the slope of the Aircraft trajectory
    double a = (x_departure - x_arrival)/(y_departure - y_arrival);
    // we compute the y coordinate of the Aircraft, using the slope, the simTime and the velocity and the y_arrival
    double difY = (v*(simTime().dbl() - par("startTime").doubleValue()))/(sqrt(1+a*a));
    if (y_departure < y_arrival) {y = y_arrival - difY;}
    else {y = y_arrival + difY;}
}

void Aircraft::refreshDisplay() const {
    // update the position on the 2D canvas, too
    getDisplayString().setTagArg("p", 0, x);
    getDisplayString().setTagArg("p", 1, y);
}

void Aircraft::finish(){

}
