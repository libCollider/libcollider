#include "ColliderPlusPlus.hpp"
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>


using namespace ColliderPlusPlus;

bool init(int argc, char* argv[], std::string &soundfile, std::string &synthDefDir);

int main(int argc, char* argv[])
{
  std::string soundfile;
  std::string synthDefDir;
  
  if(!init(argc, argv, soundfile, synthDefDir))
  {
    std::cerr 
	<< "Usage: Grain_Test <Soundfile> <SynthDefDirectory" << std::endl;
    return 1;
  }


  Client_Server cs("Server", synthDefDir);
  Buffer b(cs._nextBufferNum());
  b._readSoundFile(cs, soundfile);

  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b._getBufNum();

  Synth s(cs, "TGrain", cs._nextNodeId(), sArgs);

  char a = ' ';
  while(a != 'q')
  {
    std::cin >> a;

  } 

  s._free(cs);
  b._free(cs);
  return 0;
}

bool init(int argc, char* argv[], std::string &soundfile, std::string &synthDefDir)
{  

  if(argc != 3)
  {
    return false;
  }

  soundfile = argv[1];
  synthDefDir = argv[2];

  return true;

}
