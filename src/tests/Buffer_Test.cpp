#include "ColliderPlusPlus.hpp"
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>


using namespace ColliderPlusPlus;

int main()
{
  Client_Server cs("Server");
  Buffer b(cs._nextBufferNum());
  if(!(b._readSoundFile(cs, "/Users/administrator/Desktop/cheesecake.wav")))
	return 1;
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
