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
simple Aircraft {
    parameters:
        double startTime;
        int id; 
        
        double xpos = default(0.0);
        double ypos = default(0.0);
        @display("p=$xpos,$ypos;b=5,5,rect,red,black,2");
        
        @signal[interKTime](type="double");
        @statistic[interKTime](title="Interarrival time k";record=vector);
       
    gates:
        output outAircraft;
}
