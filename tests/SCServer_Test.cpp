#include "libcollider/libcollider.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace sc;

bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir);
  

int main(int argc, char* argv[])
{
  std::string synthDefDir;
  const char* host;
  const char* port;
  
  if(!init(argc, argv, host, port, synthDefDir))
  {
    std::cerr << "Usage SCServer_Test <host> <port> <scsyndef directory>" << std::endl;
    return 1;
  }
   
  std::cout << "\nRunning SCServer test..." << std::endl;

  SCServer cs("Server", host, port, synthDefDir);
  std::cout << "breakpoint 1" << std::endl;
  cs.dumpOSC(1);
  usleep(2000000);
 
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
