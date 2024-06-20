#include "bulk_send_service.h"

BulkSendService::BulkSendService(Host *host, Address destAddress, short port, double delay, double startTime, double stopTime) : Service(host, port) {}

void BulkSendService::send(Host *host, Address destAddress, short destPort)
{
      // 전송할 데이터를 생성
      std::string data = "";
      for (int i = 0; i < 128; i++)
      {
            data.append("AAAA");
      }

      log("sending data");
      // 앞에서 생성한 데이터를 포함하는 새로운 패킷을 생성하여 전송
      Packet *newPacket = new Packet(host->address(), destAddress, port_, destPort, data);
      host->send(newPacket);
}

void BulkSendService::onReceive(Packet *packet)
{
      delete packet;
}