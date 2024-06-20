#include "host.h"
#include <iostream>
#include <random>
#include <vector>

void Host::initialize()
{
}

void Host::send(Packet *packet)
{
      std::string from = packet->srcAddress().toString();
      std::string to = packet->destAddress().toString();
      std::string dataLength = std::to_string(packet->dataString().size());

      if (address_ == packet->srcAddress())
      {
            log("sending packet: " + packet->toString());

            size_t linkTableSize = linkTable().size();
            if (linkTableSize > 0)
            {
                  linkTable()[rand() % linkTableSize]->onReceive(this, packet);
            }
      }
}

void Host::onReceive(Packet *packet)
{

      if (address_ == packet->destAddress())
      {
            Service *service = getService(packet->destPort());

            if (service == nullptr)
            {
                  log("no service for packet: " + packet->toString());
                  delete packet;
            }
            else
            {
                  log("received packet: " + packet->toString() + ", forwarding to " + service->toString());
                  service->onReceive(packet);
            }
      }
}

Service *Host::getService(short port)
{
      for (auto *service : services_)
      {
            if (service->port() == port)
            {
                  return service;
            }
      }
      return nullptr;
}

void Host::addLink(Link *link)
{
      links_.push_back(link);
}

int Host::nextServicePort()
{
      return 1000 + static_cast<int>(services_.size());
}
