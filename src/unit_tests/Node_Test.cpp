#include "Node.hpp"
#include "Client_Server.hpp"
#include <iostream>
#include <unistd.h>
#include <map>

using namespace ColliderPlusPlus;

#define ON 1
#define OFF 2

int main()
{

 Client_Server cs = Client_Server("MyServer");
 cs._dumpOSC(ON);
 sleep(1);
 cs._loadSynthDef("/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/CentroidBing.scsyndef");

 
 std::map<std::string, float> args;
 args["freq"] = 220.0;
 Synth synth1(cs, "CentroidBing",cs._nextNodeId(), args);
  
 cs._printCurrentNodeIds();
 cs._queryNodeTree();
 sleep(1);
 
 
 cs._quit();

 return 0;
}
