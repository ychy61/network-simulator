#include "echo_service.h"

void EchoService::onReceive(Packet *packet)
{
      std::string data = packet->dataString();
      std::string fromAddress = packet->srcAddress().toString();
      std::string fromPort = std::to_string(packet->srcPort());

      log("received \"" + data + "\" from " + fromAddress + ":" + fromPort + ", send reply with same data");

      Packet *reply = new Packet(host_->address(), packet->srcAddress(), port_, packet->srcPort(), data);

      host_->send(reply);

      delete packet;
}
