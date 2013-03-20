#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <unistd.h>
#include <map>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <string>

using namespace ColliderPlusPlus;
using namespace std;

bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir);

int main(int argc, char* argv[])
{

 std::string synthDefDir;
 const char* host;
 const char* port;

 if(!init(argc, argv, host, port, synthDefDir))
 {
  std::cerr << "Usage: Node_Test <host> <port> <scsyndef directory>" << std::endl;
  return 1;
 }
   
 Client_Server cs("MyServer", host, port, synthDefDir);
 cs._dumpOSC(1);

 //random magnitude arg for CentroidBing synth
 boost::mt19937 magRng;
 boost::uniform_real<> magDist(0.01, 0.65);
 boost::variate_generator<boost::mt19937, boost::uniform_real<> > randMag(magRng, magDist);

 //random rake arg for CentroidBing synth
 boost::mt19937 rakeRng;
 boost::uniform_real<> rakeDist(0.01, 1.0);
 boost::variate_generator<boost::mt19937, boost::uniform_real<> > randRake(rakeRng, rakeDist);

 //random pan arg for CentroidBing synth
 boost::mt19937 panRng;
 boost::uniform_real<> panDist(-1.0, 1.0);
 boost::variate_generator<boost::mt19937, boost::uniform_real<> > randPan(panRng, panDist);

 //random sleep value for interesting timing
 boost::mt19937 sleepRng;
 boost::uniform_int<> sleepDist(50000, 1000000);
 boost::variate_generator<boost::mt19937, boost::uniform_int<> > randSleep(sleepRng, sleepDist);

 int count = 0;
 map<string, float> args;

 while(count < 1000) { 

 float randMagVal = randMag();
 float randRakeVal = randRake();
 float randPanVal = randPan();
 args["mag"] = randMagVal;
 args["rake"] = randRakeVal;
 args["pan"] = randPanVal;

 //Object style
 Synth synth(&cs,"CentroidBing", -1, args, 1);

 //Equiv. Message style
 //cs._createSynth("CentroidBing", -1, args);

 //Sleep for a random amount of time to make it interesting
 usleep(randSleep());
 count++;
 } 

 //All done
 sleep(1);
  return 0;
}

bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir)
{
 if(argc != 4)
 {
   return false;
 }
 
 host = argv[1];
 port = argv[2];
 synthDefDir = argv[3];

 return true;
}


