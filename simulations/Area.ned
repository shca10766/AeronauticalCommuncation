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
network Area
{
    parameters:
		double T_BS;
        @display("bgb=200,200,grey;bgu=km;bgg=100,1,red");
    submodules:
        aircraftGenerator: AircraftGenerator {
            @display("b=5,5,oval;p=99,8");
        }
        baseStation1: BaseStation {
            parameters:
                nBS = 1;
                x_BS = 50;
                y_BS = 50;
                T = T_BS;
                @display("p=50,50");
        }
        baseStation2: BaseStation {
            parameters:
                nBS = 2;
                x_BS = 150;
                y_BS = 50;
                T = T_BS;
                @display("p=150,50");
        }
        baseStation3: BaseStation {
            parameters:
                nBS = 3;
                x_BS = 50;
                y_BS = 150;
                T = T_BS;
                @display("p=50,150");
        }
        baseStation4: BaseStation {
            parameters:
                nBS = 4;
                x_BS = 150;
                y_BS = 150;
                T = T_BS;
                @display("p=150,150");
        }
        controlTower: ControlTower {
            @display("p=100,100;b=20,20,oval");
        }
    connections allowunconnected:
        baseStation1.outBS --> controlTower.inCT++;
        baseStation2.outBS --> controlTower.inCT++;
        baseStation3.outBS --> controlTower.inCT++;
        baseStation4.outBS --> controlTower.inCT++;

}
