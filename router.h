#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry
{
public:
  Address destination;
  Link *nextLink;
};

class Router : public Node
{
protected:
  virtual ~Router() {}
  std::vector<RoutingEntry> routingTable_;
  int Destination(Address dest);
public:
  void onReceive(Packet *packet) override;
};

#endif