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

package aeronauticalcommunication.simulations;

import aeronauticalcommunication.Aircraft;
import aeronauticalcommunication.AircraftGenerator;
import aeronauticalcommunication.BaseStation;
import aeronauticalcommunication.ControlTower;
//
// TODO auto-generated type
//
network Area {
    parameters: 
        bool scenario; // Define the scenario -> False: D/M/1 	True: M/M/1
       	int l; // number of BS on the length
       	int w; // number of BS on the width
       	int M; // distance between two BSs
    submodules:
        aircraftGenerator: AircraftGenerator;
        baseStation[w*l]: BaseStation;       
        
}
