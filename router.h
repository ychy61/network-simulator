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
  virtual std::string name() override { return "Router"; }
  void log(std::string message) { Node::log(message); }

public:
  void onReceive(Packet *packet) override;
};

#endif