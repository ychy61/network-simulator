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
            std::cout << "Host #" << id() << ": sending packet (from: " << from << ", to: " << to << ", " << dataLength << " bytes)" << std::endl;

            std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<std::size_t> dist(0, linkTable().size() - 1);
            linkTable()[dist(rng)]->onReceive(this, packet);
      }
      else if (address_ == packet->destAddress())
      {
            Service *service = Host::getService(packet->destPort());
            std::cout << "Host #" << id() << ": received packet, destination port: " << packet->destPort() << std::endl;
            if (service == nullptr)
            {
                  std::cout << "Host #" << id() << ": no service for packet (from: " << from << ", to: " << to << ", " << dataLength << " bytes)" << std::endl;
                  delete packet;
                  return;
            }
            service->onReceive(packet);
      }
}

void Host::onReceive(Packet *packet)
{
      if (address_ == packet->destAddress())
      {
            Service *service = getService(packet->destPort());
            if (service != nullptr)
            {
                  service->onReceive(packet);
            }
            else
            {
                  std::cerr << "Host #" << id() << ": No service available on port " << packet->destPort() << std::endl;
                  delete packet;
            }
      }
      else
      {
            std::cerr << "Host #" << id() << ": Received packet with incorrect destination address." << std::endl;
            delete packet;
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

Link *Host::getRandomLink()
{
      if (links_.empty())
      {
            return nullptr;
      }

      std::mt19937 rng(std::random_device{}());
      std::uniform_int_distribution<std::size_t> dist(0, links_.size() - 1);
      return links_[dist(rng)];
}