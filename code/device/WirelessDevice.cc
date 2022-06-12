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

#include "WirelessDevice.h"

Define_Module(WirelessDevice);

void WirelessDevice::initialize()
{
    if(strcmp("wirelessDevice1", getName()) == 0){
        cPacket *msg = new cPacket("1");
        scheduleAt(simTime(), msg);
    }
}

void WirelessDevice::handleMessage(cMessage *msg)
{
    if(strcmp(this->pktName, "1") != 0){  // trick to stop flooding

        for(auto wirelessDevice:getParentModule()->getSubmoduleNames()){
            if(strcmp(wirelessDevice.c_str(), getName()) != 0){
                cModule *target = getParentModule()->getSubmodule(wirelessDevice.c_str());

                this->pktName = msg->dup()->getName(); //// trick to stop flooding

                sendDirect(msg->dup(), 1, 2, target, "in");
            }
        }
    }
    delete(msg);
}
