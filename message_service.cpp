#include "message_service.h"

// 메시지를 전송하는 함수
void MessageService::send(std::string message)
{
    Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
    // 호스트를 통해 패킷을 전송
    host_->send(packet);
}

// 패킷을 수신했을 때 처리하는 함수
void MessageService::onReceive(Packet *packet)
{
    log("received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()));

    delete packet;
}