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
  b._readSoundFile(cs, "/Users/administrator/Music/Mastah Syphe/BULLRIDER EP");

  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b._getBufNum(); //fix this type conversion stuff
  Synth s(cs, "SoundFile_Object_Loop_Stereo", cs._nextNodeId(), sArgs);
     
  //Stress test 
  int count = 0;
  while(count < 100)
  {
    b._alloc(cs, b._getSampRate()*4, 2);
 
    b._free(cs);
    ++count;
    usleep(10000);
  }

  sleep(2);
  s._free(cs);
  b._free(cs);
  cs._quit();

  return 0;
}
