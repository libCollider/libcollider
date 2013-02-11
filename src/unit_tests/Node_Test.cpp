#include "Node.hpp"
#include "Client_Server.hpp"
#include <iostream>
#include <unistd.h>

using namespace ColliderPlusPlus;

int main()
{

 Client_Server cs = Client_Server("MyServer");
 cs._boot();
 sleep(2);
 Synth synth(cs, "default",cs._nextNodeId());
 std::cout << "Synth " << synth._getDefName() << " has Id: " << synth._getId() 
							<< std::endl;
 sleep(5);
 synth._free(cs);
// Node* node;
// node = &synth;
// std::cout << "This node has an Id: "<< (*node)._getId() << std::endl;

 return 0;
}
