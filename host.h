#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>

class Host : public Node
{
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

  std::vector<Link *> links_;
  virtual std::string name() override { return "Host"; }

public:
  Address address() { return address_; }
  Host(Address address) : address_(address) {}
  virtual ~Host()
  {
    for (auto service : services_)
    {
      delete service;
    }
    for (auto link : links_)
    {
      delete link;
    }
  }

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize();
  Service *getService(short port);
  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet);
  void onReceive(Packet *packet) override;
  void addLink(Link *link);
  int nextServicePort();
};

#endif