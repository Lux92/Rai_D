
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
    /*
 if(msg->arrivedOn("upperLayerIn")) {
     Frame *pkt = new Frame();
     pkt->encapsulate(msg);
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
             matrice[sAddr][SAddr] = RSSI;





 }}

*/
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


/*
 *  Algoritmo di Dijkstra
 *
 *  Si deve generare un SPT (Short path three) dando come ingresso una radice ( un grafo suppongo)
 *  Si costruiscono due insiemi: un insieme "A" contiene di nodi che appartengono al SPT mentre l'altro insieme
 *   "B" contiene  i nodi esclusi.
 *  Ad ogni passo dell'algoritmo si sceglie un nodo dall'insieme B che abbia la distanza minima  e lo si
 *  inserisce nell'insieme A.
 *
 *  PASSI:
 *  1) Creare un insieme sptSet che raccoglie i vertici inclusi nell' SPT ( vertici = nodi )
 *  2) Viene assegnato ad ogni nodo una distanza. Inizialmente tutti i vertici hanno distanza infinita
 *     tranne il nodo di partenza che avrà distanza 0
 *  3) Finchè sptSet non ha tutti i vertici
 *     --> Viene preso un nodo u che non è contenuto in sptSet e ha la distanza minima
 *     --> Viene aggiunto u al sptSet
 *     --> Viene aggiornata la distanza di tutti i nodi adiacenti:
 *          Per aggiornare la distanza per ogni nodo adiacente v se la somma tra la distanza tra u e il peso del
 *           lato (il collegamento) è minore della distanza di v viene aggiornata la distanza di v
 *
 *
 *  L' sptSet è inizialmente vuoto e le distanze dei vertici sono: {0, INF, INF, INF, INF, INF, INF, INF},
 *  Adesso viene preso il vertice con distanza minore ovvero --> 0
 *  Quindi  ora l'sptSet conterrà  solo il nodo sorgente. Successivamente vengo aggiornate le distanze tra il vertice 0
 *  e quelli adiacenti.
 *  L'algoritmo continua iterando questa operazione: quindi viene preso un nodo adiacente che ha il peso minore,
 *  vengono calcolati i pesi dei nodi adiacenti ( viene fatta la somma dei nodi adiacenti a quello di partenza )
 *   e vengono aggiornati gli altri
 *
 *   Adesso però non dobbiamo raggionare con le distanze ma con L'RSSI!!
 */

