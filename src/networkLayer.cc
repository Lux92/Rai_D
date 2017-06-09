
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


void dijsktraAlg(double graph[numNodi][numNodi],ins src) {

    //Function that implements Dijkstra's single source shortest path algorithm
    // for a graph represented using adjacency matrix representation
    {
         int dist[numNodi];     // The output array.  dist[i] will hold the shortest
                          // distance from src to i

         bool sptSet[numNodi]; // sptSet[i] will true if vertex i is included in shortest
                         // path tree or shortest distance from src to i is finalized

         // Initialize all distances as INFINITE and stpSet[] as false , INT_MAX
         for (int i = 0; i < numNodi; i++)
            dist[i] = INT_MAX, sptSet[i] = false;

         // Distance of source vertex from itself is always 0
         dist[src] = 0;

         // Find shortest path for all vertices
         for (int count = 0; count < numNodi-1; count++)
         {
           // Pick the minimum distance vertex from the set of vertices not
           // yet processed. u is always equal to src in first iteration.
           int u = minDistance(dist, sptSet);

           // Mark the picked vertex as processed
           sptSet[u] = true;

           // Update dist value of the adjacent vertices of the picked vertex.
           for (int v = 0; v < numNodi; v++)

             // Update dist[v] only if is not in sptSet, there is an edge from
             // u to v, and total weight of path from src to  v through u is
             // smaller than current value of dist[v]
             if (!sptSet[v] && graph[u][v] && dist[u] != INT_MIN
                                           && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
         }

         // print the constructed distance array
         printSolution(dist, V);
    }
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
// Deve restiture il nodo con RSSI maggiore!!!
// mmm ha come ingresso un vettore dist[] sto vettore deve contere i pesi (RSSI)
// Altra nota da noi dijikstra funziona al contrario quindi setto a -infinito il valore iniziale

int minDistance(int dist[], bool sptSet[], int numNodi)
{
   // Initialize min value
   int min = INT_MIN, min_index;

   for (int v = 0; v < numNodi; v++)
     if (sptSet[v] == false && dist[v] >= min)
         min = dist[v], min_index = v;

   return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d \t\t %d\n", i, dist[i]);
}


