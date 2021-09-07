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
        cPacket *msg = new cPacket("tictocMsg");
        server = getModuleByPath("wirelessDevice2");
        sendDirect(msg, 1, 50, server->gate("in"));
    }
}

void WirelessDevice::handleMessage(cMessage *msg)
{
    if(strcmp("wirelessDevice1", getName()) == 0)
        server = getModuleByPath("wirelessDevice2");
    else if(strcmp("wirelessDevice2", getName()) == 0)
        server = getModuleByPath("wirelessDevice1");

    sendDirect(msg, 1, 50, server->gate("in"));
}
