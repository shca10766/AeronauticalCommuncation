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
simple ControlTower {
    parameters:
        // Signals for statistics
        @signal[endToEndDelay](type="simtime_t");
        @signal[serviceTime](type="simtime_t");
        
        // Statistics
        @statistic[endToEndDelay](title="end-to-end delay of arrived packets";unit=s;record=vector,timeavg,mean,min,max;interpolationmode=none);
        @statistic[serviceTime](title="service time";record=vector,mean;unit=s;interpolationmode=none);
        
    gates:
        input inCT[];
}
