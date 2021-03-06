//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __RAI_D4_3_NETWORKLAYER_H_
#define __RAI_D4_3_NETWORKLAYER_H_

#include <omnetpp.h>
#include "MACAddress.h"

using namespace omnetpp;
using namespace inet;

/**
 * TODO - Generated class
 */
class NetworkLayer : public cSimpleModule
{
  protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual void handleUpperMessage(cMessage *msg);
    virtual void handleLowerMessage(cMessage * msg);

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }

       virtual void transmitFrame();
       virtual MACAddress resolveMACAddress(const char *addr);

       int numNodi;
    double **matrice;
    MACAddress destAddr;
 //   MACAddress srcAddr;


};

#endif
