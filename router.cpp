#include "router.h"
#include <iostream>
#include <string>
#include <memory>

int Router::Destination(Address dest)
{
      for (std::size_t i = 0; i < routingTable_.size(); i++)
      {
            if (routingTable_[i].destination == dest)
            {
                  return static_cast<int>(i);
            }
      }
      return -1;
}

void Router::onReceive(Packet *packet)
{
      std::string from = packet->srcAddress().toString();
      std::string to = packet->destAddress().toString();
      std::string dataLength = std::to_string(packet->dataString().size());

      int routingTableIndex = Destination(packet->destAddress());
      if (routingTableIndex == -1)
      {
            log("no route for packet: " + packet->toString());
            delete packet;
            return;
      }
      // 패킷을 다음 링크로 전달
      std::string linkId = routingTable_[routingTableIndex].nextLink->toString();
      log("forwarding packet: " + packet->toString() + " to " + linkId);
      routingTable_[routingTableIndex].nextLink->onReceive(this, packet);
}
