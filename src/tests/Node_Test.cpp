#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <unistd.h>
#include <map>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <string>

using namespace ColliderPlusPlus;
using namespace std;
#define ON 1
#define OFF 2

int main()
{
 Client_Server cs = Client_Server("MyServer");
 cs._loadSynthDef("../../synthdefs/CentroidBing.scsyndef");
 cs._queryNodeTree();

 map<string, float> args;
 boost::mt19937 rng;
 boost::uniform_real<> dist(0.1, 1.0);
 boost::variate_generator<boost::mt19937, boost::uniform_real<> > randMag(rng, dist);

 int count = 0;
 while(count < 20) { 
 float result = randMag();
 std::cout << result << std::endl;
 args["mag"] = result;
 Synth synth(cs,"CentroidBing",-1, args);
 usleep(250000);
 count++;
 } 
 sleep(1);
 cs._quit();

 return 0;
}
