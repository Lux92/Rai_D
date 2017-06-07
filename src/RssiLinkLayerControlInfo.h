#ifndef RSSILINKLAYERCONTROLINFO_H_
#define RSSILINKLAYERCONTROLINFO_H_

#include <SimpleLinkLayerControlInfo.h>

using namespace inet;

class RssiLinkLayerControlInfo: public SimpleLinkLayerControlInfo {
protected:
    double rssi;

public:
    RssiLinkLayerControlInfo() : SimpleLinkLayerControlInfo(), rssi(0) {}
    RssiLinkLayerControlInfo(const RssiLinkLayerControlInfo& other);
    RssiLinkLayerControlInfo& operator=(const RssiLinkLayerControlInfo& other);

    virtual RssiLinkLayerControlInfo *dup() const override { return new RssiLinkLayerControlInfo(*this); }

    virtual void setRSSI(double val) { this->rssi = val; }
    virtual double getRSSI() const { return this->rssi; }
};

#endif /* RSSILINKLAYERCONTROLINFO_H_ */
