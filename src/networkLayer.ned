//Livello di rete

package rai_d4_3;

simple NetworkLayer
{

    
    parameters:
        string DestAddr;
        string SrcAddr;
        int numNodi = default(3);
        double RSSI;
        
        
    gates:
        input upperLayerIn;
        output upperLayerOut;
        input lowerLayerIn;
        output lowerLayerOut;

}
