#include "message_service.h"

void MessageService::send(std::string message)
{
    //     std::cout << "MessageService: Sending message from Host #" << host_->id() << std::endl;
    Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
    host_->send(packet);
}

void MessageService::onReceive(Packet *packet)
{
    std::cout << "MessageService: received \"" << packet->dataString() << "\" from " << packet->srcAddress().toString() << ":" << std::to_string(packet->srcPort()) << std::endl;

    delete packet;
}