
#ifndef __RAI_D4_3_APPLAYER_H_
#define __RAI_D4_3_APPLAYER_H_

#include <omnetpp.h>
#include <networkLayer.h>



using namespace omnetpp;
using namespace inet;



class AppLayer : public cSimpleModule
{
  protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);







        simtime_t period;
        simtime_t startTime;
        unsigned int dataSize;


};

#endif
