#include "OscMessenger.hpp"

#include <iostream>
using namespace ColliderPlusPlus;

int main()
{

  OscMessenger::OscMessenger oscm;

 // oscm._setPort("57110");
 // oscm._setHost("127.0.0.1");

  std::cout << "Port: " << oscm._getPort() << std::endl;
  std::cout << "Host: " << oscm._getHost() << std::endl;

 // oscm._createSynth("default", 1, 1);
 // oscm._killSynth(1,1);

  return 0;
}
