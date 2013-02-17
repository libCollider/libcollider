#include "ColliderPlusPlus.hpp"
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>


using namespace ColliderPlusPlus;

#define SYNTH_DIR "/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/"

int main(int argc, char* argv[])
{
  std::string soundfile;

  if(argc != 2)
  {
    std::cerr << "Usage: Buffer_Test <Soundfile>" << std::endl;
    return 1;
  }

  soundfile = argv[1];  
  
  Client_Server cs("Server", SYNTH_DIR);
  Buffer b(cs._nextBufferNum());
  b._readSoundFile(cs, soundfile);
  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b._getBufNum();
  sArgs["stutterRate"] = 7;
  sArgs["rate"] = 3.0;
  Synth s(cs, "SoundFile_Stutter_Loop_Stereo", cs._nextNodeId(), sArgs);
  sleep(10);

  s._free(cs);
  b._free(cs);
  //cs._quit();
  return 0;
}
