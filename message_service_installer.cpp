#include "message_service_installer.h"

MessageService *MessageServiceInstaller::install(Host *host)
{
      MessageService *service = new MessageService(host, host->nextServicePort(), destAddress_, destPort_);
      ServiceInstaller::install(host, service);
      return service;
}