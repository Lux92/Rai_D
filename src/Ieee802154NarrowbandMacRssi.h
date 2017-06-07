#ifndef __TESTWIRELESS_IEEE802154NARROBANDMACRSSI_H_
#define __TESTWIRELESS_IEEE802154NARROBANDMACRSSI_H_

#include <omnetpp.h>
#include "CSMA.h"

using namespace omnetpp;
using namespace inet;

class Ieee802154NarrowbandMacRssi : public CSMA {
  protected:
    virtual cPacket *decapsMsg(CSMAFrame *macPkt);

};

#endif
