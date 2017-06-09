
#include "appLayer.h"


Define_Module(AppLayer);

using namespace std;
using namespace inet;




void AppLayer::initialize(int stage) {
    if(stage == INITSTAGE_LOCAL) {
        period = par("Period");
        startTime = par("StartTime");
        dataSize = par("DataSize");
        cPacket *pkt = new cPacket();
                      send(pkt,"lowerLayerOut");

     }else if(stage == INITSTAGE_APPLICATION_LAYER) {


}
}

void AppLayer::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()) {

        cPacket *pkt = new cPacket();
        send(pkt,"lowerLayerOut");
    }


            if(strcmp(msg->getName(), "StartTimer")== 0) {
                send(msg,"lowerLayerOut");
                scheduleAt(simTime()+period, msg);
                return;
            }
            error("Unknown Timer");
        }


