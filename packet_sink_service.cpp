#include "packet_sink_service.h"

void PacketSinkService::onReceive(Packet *packet)
{
      totalPacketSize += packet->data().size();
      log("received total " + std::to_string(totalPacketSize) + " bytes");
      delete packet;
};