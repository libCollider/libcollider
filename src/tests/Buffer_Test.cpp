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
  b._readSoundFile(cs, "/Users/administrator/Desktop/cheesecake.aiff");

  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b._getBufNum();
  Synth s(cs, "SoundFile_Stutter_Loop_Stereo", cs._nextNodeId(), sArgs);
  sleep(24);
     
  //Stress test - read soundfile into new buffer as fast as possible then free - 100 times
  //while sound created above plays continuously
 /* int count = 0;
  while(count < 100)
  {
    Buffer d(cs._nextBufferNum());
    d._readSoundFile(cs, "/Users/administrator/Desktop/bullrider.aiff");
    d._free(cs);
    ++count;
  }*/

  s._free(cs);
  b._free(cs);
  cs._quit();

  return 0;
}
