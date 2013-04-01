#include "ColliderPlusPlus.hpp"
#include <unistd.h>
#include <iostream>
#include <map>
#include <string>

using namespace ColliderPlusPlus;

#define TIME_GRANULARITY_MICROSECONDS 500000.0f

float getScaledTime(float durationSeconds, float granularity);
void run_time(float seconds, float granularityMicroseconds);
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
    std::cerr << "Usage Buffer_Test <host> <port> <soundfile> <scsyndef directory>" << std::endl;
    return 1;
  }

  Client_Server cs("Server", host, port, synthDefDir);
  Buffer b(&cs, cs.nextBufferNum());
  b.allocRead(soundfile);
  std::map<std::string, float> sArgs;
  sArgs["bufnum"] = b.getBufNum();
  sArgs["stutterRate"] = 7;
  sArgs["rate"] = 3.0;
  Synth s(&cs, "SoundFile_Stutter_Loop_Stereo", cs.nextNodeId(), sArgs, 1);

  int count = 0;
  float scaledTime = getScaledTime(2, TIME_GRANULARITY_MICROSECONDS);
  while(count < scaledTime )
  {
    sArgs["stutterRate"] *= 0.9;
    sArgs["rate"] *= 0.9;
    s.set(sArgs);
    usleep(TIME_GRANULARITY_MICROSECONDS);
    ++count;
  }
  
  s.stop();
  std::map<std::string, float> cArgs;
  cArgs["bufnum"] = b.getBufNum();
  cArgs["amp"] = 1.0;
  Synth c(&cs, "SoundFile_Event_Stereo", cs.nextNodeId(), cArgs, 1);
  c.query();
 
  run_time(9.85, TIME_GRANULARITY_MICROSECONDS);

  cArgs["rate"] = 1.5;
  c.set(cArgs); 
  
  run_time(5, TIME_GRANULARITY_MICROSECONDS);

  cArgs["rate"] = 1.0;
  c.set(cArgs);
    
  run_time(20, TIME_GRANULARITY_MICROSECONDS);

  count = 0;
  scaledTime = getScaledTime(4.5, TIME_GRANULARITY_MICROSECONDS);
  while(count < scaledTime )
  {
    cArgs["rate"] *= 0.9;
    c.set(cArgs);
    usleep(TIME_GRANULARITY_MICROSECONDS);
    ++count;
  }
 
  count = 0;
  scaledTime = getScaledTime(15, 250000);
  while(count < scaledTime )
  {
    cArgs["rate"] += 0.01;
    c.set(cArgs);
    usleep(250000);
    ++count;
  }
  
  run_time(10, TIME_GRANULARITY_MICROSECONDS);

  count = 0;
  scaledTime = getScaledTime(15, TIME_GRANULARITY_MICROSECONDS);
  while(count < scaledTime )
  {
    cArgs["rate"] += 0.01;
    c.set(cArgs);
    usleep(TIME_GRANULARITY_MICROSECONDS);
    ++count;
  }

  run_time(10, TIME_GRANULARITY_MICROSECONDS);
  
  count = 0;
  scaledTime = getScaledTime(20, TIME_GRANULARITY_MICROSECONDS);
  while(count < scaledTime )
  {
    cArgs["amp"] *= 0.8;
    c.set(cArgs);
    usleep(TIME_GRANULARITY_MICROSECONDS);
    ++count;
  }
  
  c.stop();
  b.free();

  return 0;
}
  
float getScaledTime(float duration, float granularity)
{
  float granSeconds = granularity * 0.000001;
  float scaledTime;
  return scaledTime = duration/granSeconds;
}

void run_time(float seconds, float granularityMicroseconds)
{
  int count = 0;
  float scaledTime = getScaledTime(seconds, granularityMicroseconds);
  while(count < scaledTime)
  {
    usleep(granularityMicroseconds); 
    ++count; 
  }
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
