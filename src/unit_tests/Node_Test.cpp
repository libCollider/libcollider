#include "Node.hpp"
#include "Client_Server.hpp"
#include <iostream>
#include <unistd.h>

using namespace ColliderPlusPlus;

#define ON 1
#define OFF 2

int main()
{

 Client_Server cs = Client_Server("MyServer");
 cs._dumpOSC(ON);
 cs._loadSynthDef("/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/CentroidBing.scsyndef");
 Synth synth(cs, "default",cs._nextNodeId());
 std::cout << "Synth " << synth._getDefName() << " has Id: " << synth._getId() << std::endl;
 cs._printCurrentNodeIds();
 cs._queryNodeTree();
 sleep(3);
 synth._free(cs);
 cs._quit();

 return 0;
}
