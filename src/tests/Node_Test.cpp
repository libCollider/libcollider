#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <unistd.h>
#include <map>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <string>

using namespace ColliderPlusPlus;
using namespace std;

#define SYNTH_DIR "/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/"

int main()
{
 Client_Server cs = Client_Server("MyServer", SYNTH_DIR);

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
 boost::uniform_int<> sleepDist(5000, 110000);
 boost::variate_generator<boost::mt19937, boost::uniform_int<> > randSleep(sleepRng, sleepDist);

 int count = 0;
 map<string, float> args;

 while(count < 1000) { 

 float randMagVal = randMag();
 float randRakeVal = randRake();
 float randPanVal = randPan();
 std::cout << randMagVal << std::endl;
 std::cout << randRakeVal << std::endl;
 args["mag"] = randMagVal;
 args["rake"] = randRakeVal;
 args["pan"] = randPanVal;

 //Object style
 Synth synth(cs,"CentroidBing",-1, args);

 //Equiv. Message style
 //cs._createSynth("CentroidBing", -1, args);

 //Sleep for a random amount of time to make it interesting
 usleep(randSleep());
 count++;
 } 

 //All done
 sleep(1);
 //cs._quit();

 return 0;
}



