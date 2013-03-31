#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace ColliderPlusPlus;

bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir);
  

int main(int argc, char* argv[])
{
  std::string synthDefDir;
  const char* host;
  const char* port;
  
  if(!init(argc, argv, host, port, synthDefDir))
  {
    std::cerr << "Usage Client_Server_Test <host> <port> <scsyndef directory>" << std::endl;
    return 1;
  }
   
  std::cout << "\nRunning Client_Server test..." << std::endl;

  Client_Server cs("Server", host, port, synthDefDir);
  cs.dumpOSC(1);
  cs.allocBuffer(cs.nextBufferNum(), 1024, 2);
  cs.status();

  usleep(2000000);
  cs.quit();   

  return 0;
}
  
bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir)
{
  if(argc != 4)
  {
    return false;
  }

  host = argv[1];
  port = argv[2];
  synthDefDir = argv[3]; 
 
  return true;
}
