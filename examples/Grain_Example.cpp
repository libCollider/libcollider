#include "libcollider/libcollider.hpp"
#include <iostream>
#include <map>
#include <string>


using namespace sc;

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

  SCServer cs("Server", host, port, synthDefDir);
  cs.dumpOSC(1);
  
  Buffer b(&cs, cs.nextBufferNum());
  b.allocRead(soundfile);

  if(b.getChanNum() == 2)
  {
     std::cerr << "\nSoundfile must be mono for this module! Exiting." << std::endl;
     b.free();
     return 1;
  }

  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b.getBufNum();

  Synth s(&cs, "TGrain2", cs.nextNodeId(), sArgs, 1);
  cs.queryNodeTree();
  
  std::cout << "\nType 'q' and enter to quit\n" << std::endl;

  char a;
  while(a != 'q')
  {
    std::cin >> a;
  } 

  b.free();

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
