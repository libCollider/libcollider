#include "ColliderPlusPlus.hpp"
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>

using namespace ColliderPlusPlus;

#define TIME_GRANULARITY_MICROSECONDS 500000.0f

float getScaledTime(int durationSeconds, float granularity);

int main(int argc, char* argv[])
{
  std::string soundfile;
  std::string synthDefDir;
  int playbackTime;

  if(argc != 4)
  {
    std::cerr 
	<< "Usage: Buffer_Test <Soundfile> <Playback Time> <SynthDefDirectory>" << std::endl;
    return 1;
  }

  soundfile = argv[1];
  playbackTime = std::atoi(argv[2]);
  synthDefDir = argv[3];  
  
  Client_Server cs("Server", synthDefDir);
  Buffer b(cs._nextBufferNum());
  b._readSoundFile(cs, soundfile);
  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b._getBufNum();
  sArgs["stutterRate"] = 7;
  sArgs["rate"] = 3.0;
  Synth s(cs, "SoundFile_Stutter_Loop_Stereo", cs._nextNodeId(), sArgs);

  int count = 0;
  float scaledTime = getScaledTime(playbackTime, TIME_GRANULARITY_MICROSECONDS);
  std::cout<< "Playing for: " << playbackTime << " seconds" << std::endl;
  while(count < scaledTime )
  {
    sArgs["stutterRate"] *= 0.9;
    sArgs["rate"] *= 0.9;
    s._set(cs, sArgs);
    usleep(TIME_GRANULARITY_MICROSECONDS);
    ++count;
  }

  s._free(cs);
  b._free(cs);
  //cs._quit();
  return 0;
}

float getScaledTime(int duration, float granularity)
{
  float granSeconds = granularity * 0.000001;
  float scaledTime;
  return scaledTime = duration/granSeconds;
}
