#include "echo_service.h"

void EchoService::onReceive(Packet *packet)
{
      // 수신된 데이터와 주소 정보 추출
      std::string data = packet->dataString();
      std::string fromAddress = packet->srcAddress().toString();
      std::string fromPort = std::to_string(packet->srcPort());

      // EchoService가 패킷을 받았다는 것을 로그로 출력
      std::cout << "EchoService: received \"" << data << "\" from " << fromAddress << ":" << fromPort << ", send reply with same data" << std::endl;

      // 응답 패킷 생성: 송신자의 주소와 포트를 목적지로 설정하여 동일한 데이터를 포함한 패킷을 생성
      Packet *reply = new Packet(host_->address(), packet->srcAddress(), port_, packet->srcPort(), data);

      // 호스트를 통해 응답 패킷 전송
      host_->send(reply);

      // 수신된 패킷 처리 완료 후 메모리 해제
      delete packet;
}
