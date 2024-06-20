#include "link_installer.h"

Link *LinkInstaller::install(Node *a, Node *b, double delay)
{
      Link *link = new Link(a, b, delay);
      a->linkTable_.push_back(link);
      b->linkTable_.push_back(link);
      return link;
}