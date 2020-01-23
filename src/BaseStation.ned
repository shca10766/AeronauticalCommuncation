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
simple BaseStation {
    parameters:
        int nBS;
        int x_BS;
        int y_BS;
        int M = default(100);
        
        //queue icon
        @display("i=block/queue;q=queue");
        
        // signals
        @signal[queueLength](type="long");
        @signal[queueingTime](type="simtime_t");
        @signal[servingTime](type="simtime_t");
        @signal[busy](type="bool");
        
        // statistics
        @statistic[queueLength](title="queue length";record=vector,timeavg,max;interpolationmode=sample-hold);
        @statistic[queueingTime](title="queueing time at dequeue";record=vector?,mean,max;unit=s;interpolationmode=none);
        @statistic[servingTime](title="service time";record=vector?,mean,max;unit=s;interpolationmode=none);
        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);
		
		// characteristic of the queue
        int capacity = default(-1);    // unlimited queue
        bool fifo = default(true);     // works as a queue (fifo=true)
        
        //For Scenario 2
        volatile double serviceTime @unit(s); // exponential
    gates:
        input inBS[];
        output outBS;
}
