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

package rai_d4_3.simulations;

import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.physicallayer.ieee802154.packetlevel.Ieee802154NarrowbandScalarRadioMedium;
import rai_d4_3.Node;


network Test
{
    int numNodes;
    
    submodules:
       
     
        
         node[numNodes]: Node {
            @display("p=132,49");
        }
        radio: Ieee802154NarrowbandScalarRadioMedium {
            @display("p=55,39");
        }
    connections allowunconnected:
}
