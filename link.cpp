#include "link.h"
#include "node.h"
#include <iostream>

void Link::onReceive(Node *sender, Packet *packet)
{
    std::string packetId = packet->toString();
    std::string senderId = sender->toString();
    Node *otherNode = other(sender);

    log("packet in: " + packetId + " from " + senderId);
    Simulator::schedule(Simulator::now() + this->delay(), [this, packet, otherNode]()
                        { this->receive(otherNode, packet); });
}

void Link::receive(Node *sender, Packet *packet)
{
    log("packet out: " + packet->toString() + " to " + sender->toString());
    sender->onReceive(packet);
}