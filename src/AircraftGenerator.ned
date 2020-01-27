//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package aeronauticalcommunication;

//
// TODO auto-generated type
//
simple AircraftGenerator {
    parameters:
        double k_generator @unit(s); // time between two generation of a packet for A/Cs
        double t_generator @unit(s); // handover operation period
        volatile double interArrivalTime @unit(s); // time between generated Aircraft
        int nbAircraft = default(-1); // number of Aircraft to be generated (-1 means no limit)
        double startTime @unit(s) = default(interArrivalTime); // when the AircraftGenerator creates the first Aircraft
        double stopTime @unit(s) = default(-1s); // when the AircraftGenerator stops the Aircraft generation (-1 means no limit)
}