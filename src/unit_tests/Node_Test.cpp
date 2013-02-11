#include "Node.hpp"
#include <iostream>

using namespace ColliderPlusPlus;

int main()
{

 Synth synth("default",1);
 std::cout << "Synth " << synth._getDefName() << " has Id: " << synth._getId() 
							<< std::endl;
// Node* node;
// node = &synth;
// std::cout << "This node has an Id: "<< (*node)._getId() << std::endl;

 return 0;
}
