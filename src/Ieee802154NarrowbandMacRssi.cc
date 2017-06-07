#include "Ieee802154NarrowbandMacRssi.h"
#include "RssiLinkLayerControlInfo.h"

Define_Module(Ieee802154NarrowbandMacRssi);

cPacket *Ieee802154NarrowbandMacRssi::decapsMsg(CSMAFrame *macPkt) {
    RssiLinkLayerControlInfo *cCtrlInfo = new RssiLinkLayerControlInfo();
    auto indication = check_and_cast<const ReceptionIndication *>(macPkt->getControlInfo());
    cPacket *msg = macPkt->decapsulate();
    cCtrlInfo->setRSSI((indication->getMinSNIR()));
    cCtrlInfo->setSrc(macPkt->getSrcAddr());
    msg->setControlInfo(cCtrlInfo);

    return msg;
}
