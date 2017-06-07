
#include "appLayer.h"


Define_Module(AppLayer);

void AppLayer::initialize()
{
            period = par("Period");
            startTime = par("StartTime");
            dataSize = par("DataSize");

            if(startTime.dbl() >= 0) {
            cMessage *msg = new cMessage("StartTimer");
            scheduleAt(startTime, msg);
            }
}

void AppLayer::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()) {
            if(strcmp(msg->getName(), "StartTimer")== 0) {
                send(msg,"lowerLayerOut");
                scheduleAt(simTime()+period, msg);
                return;
            }
            error("Unknown Timer");
        }


}
