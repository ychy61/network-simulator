#include "echo_service_installer.h"

EchoService *EchoServiceInstaller::install(Host *host)
{
      EchoService *service = new EchoService(host, listenPort_);
      ServiceInstaller::install(host, service);
      return service;
}