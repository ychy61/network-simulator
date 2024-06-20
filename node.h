#ifndef NODE_H
#define NODE_H

#include "object.h"
#include "link.h"
#include "packet.h"
#include <vector>

class Node : Object
{
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;
  std::vector<Link *> linkTable_;

protected:
  void log(std::string message) { Object::log(message); }

public:
  Node() : id_(nextId_++) {}
  virtual ~Node() {}
  int id() const { return id_; }
  std::vector<Link *> linkTable() { return linkTable_; }

  virtual void onReceive(Packet *packet) = 0;
  std::string toString() { return Object::toString(); }
};

#endif