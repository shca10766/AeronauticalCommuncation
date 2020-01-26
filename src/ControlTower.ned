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
        @signal[endToEndDelayB1](type="simtime_t");
        @signal[endToEndDelayB2](type="simtime_t");
        @signal[endToEndDelayB3](type="simtime_t");
        @signal[endToEndDelayB4](type="simtime_t");
        @signal[serviceTime](type="simtime_t");
        
        // Statistics -- we use remover repeat to do a warmup period filter
        @statistic[endToEndDelayB1](title="end-to-end delay of arrived packets from B1";unit=s;record=vector(removeRepeats),mean,min,max;interpolationmode=none);
        @statistic[endToEndDelayB2](title="end-to-end delay of arrived packets from B2";unit=s;record=vector(removeRepeats),mean,min,max;interpolationmode=none);
        @statistic[endToEndDelayB3](title="end-to-end delay of arrived packets from B3";unit=s;record=vector(removeRepeats),mean,min,max;interpolationmode=none);
        @statistic[endToEndDelayB4](title="end-to-end delay of arrived packets from B4";unit=s;record=vector(removeRepeats),mean,min,max;interpolationmode=none);
        @statistic[serviceTime](title="service time";record=vector(removeRepeats),mean;unit=s;interpolationmode=none);
        
    gates:
        input inCT[];
}
