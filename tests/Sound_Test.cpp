#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <string>
#include <unistd>

using namespace ColliderPlusPlus

bool init(int argc, char* argv[], const char* &host, const char* &port,
			 std::string &soundfile, std::string &synthDefDir);
  

int main(int argc, char* argv[])
{
  std::string soundfile;
  std::string synthDefDir;
  const char* host;
  const char* port;
  
  if(!init(argc, argv, host, port, soundfile, synthDefDir))
  {
    std::cerr << "Usage Sound_Test <host> <port> <soundfile> <scsyndef directory>" << std::endl;
    return 1;
  }

  Client_Server cs("Server", host, port, synthDefDir);
  Sound(cs, soundfile, NEW_PAUSED);
 

  return 0;
}
  
bool init(int argc, char* argv[], const char* &host, const char* &port,
				 std::string &soundfile, std::string &synthDefDir)
{
  if(argc != 5)
  {
    return false;
  }

  host = argv[1];
  port = argv[2];
  soundfile = argv[3];
  synthDefDir = argv[4]; 
 
  return true;
}
