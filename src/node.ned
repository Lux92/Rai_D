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

package rai_d4_3;

import inet.linklayer.contract.IWirelessNic;
import inet.mobility.contract.IMobility;
import inet.networklayer.common.InterfaceTable;


module Node
{
    parameters:
        @networkNode;
        string mobilityType = default("StationaryMobility");
        string nicType = default("Ieee802154NarrowbandNicRssi");
        *.mobilityModule = default(mobilityType != "" ? absPath(".mobility") : "");
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        @display("bgb=284,339");
    gates:
        input channelIn;
    submodules:
        interfaceTable: InterfaceTable {
            @display("p=50,87");
        }
        app: AppLayer {
            @display("p=134,30");
        }
        networkLayer: NetworkLayer {
            @display("p=134,170;is=l");
        }
        iWirelessNic: <nicType> like IWirelessNic {
            @display("p=134,287");
            radio.transmitter.preambleDuration = 192us;
            radio.bandwidth = 2.8MHz;
        }

        mobility: <mobilityType> like IMobility {
            @display("p=252,87");
        }
    connections:
        app.lowerLayerOut --> networkLayer.upperLayerIn;
        networkLayer.upperLayerOut --> app.lowerLayerIn;
        networkLayer.lowerLayerOut --> iWirelessNic.upperLayerIn;
        iWirelessNic.upperLayerOut --> networkLayer.lowerLayerIn;
        channelIn --> iWirelessNic.radioIn;
}
