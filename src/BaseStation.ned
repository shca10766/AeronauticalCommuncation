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
        double T;
        
        // queue icon
        @display("i=block/queue;q=queue");
        
        // signals
        @signal[queueLength](type="long");
        @signal[serviceTime](type="simtime_t");
        
        // statistics -- we use remover repeat to do a warmup period filter
        @statistic[queueLength](title="queue length";record=vector(removeRepeats),mean,min,max;interpolationmode=sample-hold);
        @statistic[serviceTime](title="service time";record=vector(removeRepeats),mean;unit=s;interpolationmode=none);
       
		// characteristic of the queue
        int capacity = default(-1);    // unlimited queue
        bool fifo = default(true);     // works as a queue (fifo=true)
    gates:
        input inBS[];
        output outBS;
}
