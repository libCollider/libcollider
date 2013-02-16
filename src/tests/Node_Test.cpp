#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <unistd.h>
#include <map>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <string>

using namespace ColliderPlusPlus;
using namespace std;

int main()
{
 Client_Server cs = Client_Server("MyServer");
 cs._queryNodeTree();

 //random magnitude arg for CentroidBing synth
 boost::mt19937 rng;
 boost::uniform_real<> dist(0.1, 1.0);
 boost::variate_generator<boost::mt19937, boost::uniform_real<> > randMag(rng, dist);

 //random sleep value for interesting timing
 boost::mt19937 rng2;
 boost::uniform_int<> dist2(20000, 750000);
 boost::variate_generator<boost::mt19937, boost::uniform_int<> > randSleep(rng2, dist2);

 int count = 0;
 map<string, float> args;

 while(count < 1000) { 

 //Random magnitude arg for CentroidBing Synth
 float result = randMag();
 std::cout << result << std::endl;
 args["mag"] = result;

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
 cs._quit();

 return 0;
}



