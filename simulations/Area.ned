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
        
    submodules:
        aircraftGenerator: AircraftGenerator;
        baseStation1: BaseStation {
            parameters:
                nBS = 1;
                x_BS = 50;
                y_BS = 50; 
        }
        baseStation2: BaseStation {
            parameters:
                nBS = 2;
                x_BS = 150;
                y_BS = 50; 
        }
        baseStation3: BaseStation {
            parameters:
                nBS = 3;
                x_BS = 50;
                y_BS = 150; 
        }
        baseStation4: BaseStation {
            parameters:
                nBS = 4;
                x_BS = 150;
                y_BS = 150; 
        }
        controlTower: ControlTower;
        aircraft: Aircraft;
	connections allowunconnected:
	    baseStation1.outBS --> controlTower.inCT++;
	    baseStation2.outBS --> controlTower.inCT++;
	    baseStation3.outBS --> controlTower.inCT++;
	    baseStation4.outBS --> controlTower.inCT++;
	    
}
