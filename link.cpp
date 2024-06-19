#include "link.h"
#include "node.h"
#include <iostream>

void Link::onReceive(Node* sender, Packet* packet) {
    Node* receiver = other(sender);
    std::cout << "Link: forwarding packet from node #" << sender->id() << ", to node #" << receiver->id() << std::endl;
    receiver->onReceive(packet);
}
