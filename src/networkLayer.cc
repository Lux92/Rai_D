
#include "networkLayer.h"

#include "Ieee802Ctrl.h"
#include "MACAddress.h"
#include "InterfaceTable.h"
#include "RssiLinkLayerControlInfo.h"

Define_Module(NetworkLayer);

using namespace std;

void NetworkLayer::initialize(int stage)
{
    if(stage == INITSTAGE_LOCAL) {
    numNodi = par("numNodi");
            matrice = new double *[numNodi];
            for(int i = 0; i< numNodi ; i++){
                        matrice[i] = new double[numNodi];
                    for(int j=0;j < numNodi; j++){
                        matrice[i][j] = -1;
                        cout << "val:" << matrice[i][j] << endl;
                    }}} else if(stage == INITSTAGE_APPLICATION_LAYER) {
                        const char *dAddr = par("DestAddr").stringValue();
                   //     destAddr = resolveMACAddress(dAddr);
                        }
}


void NetworkLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void NetworkLayer::transmitFrame() {
    IMACProtocolControlInfo *ctrl = new Ieee802Ctrl();
  //   ctrl->setDestinationAddress(destAddr);
    //Frame *pkt = new Frame();
   // pkt->setControlInfo(dynamic_cast<cObject *>(ctrl));
    // send(pkt,"lowerLayerOut");
}

MACAddress NetworkLayer::resolveMACAddress(const char *addr) {
    cTopology topo("topo");
    topo.extractByProperty("networkNode");
    for (int i = 0; i < topo.getNumNodes(); i++) {
        cModule *dhost = topo.getNode(i)->getModule();
        if(strcmp(dhost->getFullName(), addr) == 0) {
            IInterfaceTable *it = dynamic_cast<IInterfaceTable *>(dhost->getSubmodule("interfaceTable"));
            return (it->getInterface(0))->getMacAddress();
        }
    }
    return MACAddress::UNSPECIFIED_ADDRESS;
}
