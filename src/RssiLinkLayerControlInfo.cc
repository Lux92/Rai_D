#include <RssiLinkLayerControlInfo.h>

RssiLinkLayerControlInfo::RssiLinkLayerControlInfo(const RssiLinkLayerControlInfo& other)
                                                    : SimpleLinkLayerControlInfo(other) {
    this->rssi = other.rssi;
}

RssiLinkLayerControlInfo& RssiLinkLayerControlInfo::operator=(const RssiLinkLayerControlInfo& other) {
    SimpleLinkLayerControlInfo::operator=(other);
    this->rssi = other.rssi;
    return *this;
}
