
#include "networkLayer.h"
#include "Frame_m.h"
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
            RSSI = par("RSSI");
            for(int i = 0; i< numNodi ; i++){
                        matrice[i] = new double[numNodi];
                    for(int j=0;j < numNodi; j++){
                        matrice[i][j] = -1;
                        cout << "val:" << matrice[i][j] << endl;
                    }}} else if(stage == INITSTAGE_APPLICATION_LAYER) {
                        const char *dAddr = par("DestAddr").stringValue();
                        const char *sAddr = par("SrcAddr").stringValue();
                        destAddr = resolveMACAddress(dAddr);
                        }
}


void NetworkLayer::handleMessage(cMessage *msg)
{

 if(msg->arrivedOn("upperLayerIn")) {
     Frame *pkt = new Frame();

     pkt->encapsulate((dynamic_cast<Frame *>(msg)));

    transmitFrame();
}
 else if(msg->arrivedOn("lowerLayerIn")){
     Frame *pkt = dynamic_cast< Frame *>(msg);
         RssiLinkLayerControlInfo *ctrl = dynamic_cast<RssiLinkLayerControlInfo *>(pkt->removeControlInfo());
         if(ctrl != nullptr) {
             EV << "Packet received with RSSI: " << ctrl->getRSSI() << " W" << endl;
             // Ora bisogna aggiungerlo alla matrice
             //Forse ci vuole il puntatore
             RSSI = ctrl->getRSSI();
             MACAddress SAddr = ctrl->getSourceAddress();
             delete ctrl;
           //  matrice[sAddr][SAddr] = RSSI;
            cPacket *pkt2 = pkt->decapsulate();
            send(pkt2,"upperLayerOut");






 }}


}
// Messaggio proveniente dal livello applicativo :
// Bisogna incapsularlo e mandarlo al livello fisico
void NetworkLayer::handleUpperMessage(cMessage *msg) {

    }




//Messaggio proventiente dal livello fisico:
// bisogna decapsularlo e leggere sorgente e destinazione
// poi si deve estrarre l'RSSI e inserirlo nella tabella insieme all' ?"indirizzo"? del nodo
void NetworkLayer::handleLowerMessage(cMessage *msg) {

}

void NetworkLayer::transmitFrame() {
    IMACProtocolControlInfo *ctrl = new Ieee802Ctrl();
    ctrl->setDestinationAddress(destAddr);
    ctrl->setSourceAddress(srcAddr);
   Frame *pkt = new Frame();
    pkt->setControlInfo(dynamic_cast<cObject *>(ctrl));
     send(pkt,"lowerLayerOut");
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
