#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <map>
#include <string>


using namespace ColliderPlusPlus;

bool init(int argc, char* argv[], const char* &host,
	 const char* &port, std::string &soundfile, std::string &synthDefDir);

int main(int argc, char* argv[])
{
  std::string soundfile;
  std::string synthDefDir;
  const char* host;
  const char* port;
  
  if(!init(argc, argv, host, port, soundfile, synthDefDir))
  {
    std::cerr 
	<< "Usage: Grain_Test <host> <port> <soundfile path> <scsyndef directory>" << std::endl;
    return 1;
  }

  Client_Server cs("Server", host, port, synthDefDir);
  cs._dumpOSC(1);
  
  Buffer b(&cs, cs._nextBufferNum());
  b._allocRead(soundfile);

  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b._getBufNum();

  Synth s(&cs, "TGrain2", cs._nextNodeId(), sArgs, 1);
  cs._queryNodeTree();
  
  std::cout << "\nType 'q' and enter to quit\n" << std::endl;

  char a;
  while(a != 'q')
  {
    std::cin >> a;
  } 

  b._free();

  return 0;
}

bool init(int argc, char* argv[], const char* &host,
	 const char* &port, std::string &soundfile, std::string &synthDefDir)
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
