#include "Client_Server.hpp"
#include <iostream>

using ColliderPlusPlus::Client_Server;

int main()
{

  std::cout << "Creating a default Client_Server" << std::endl;

  Client_Server cs;

  std::cout << "The server name is: " << cs._getName() << std::endl;
  
  std::cout << "Next node id is: " <<cs._nextNodeID() << std::endl;

  for (int i = 0; i < 5; ++i)
  {
    cs._nextNodeID();
  }

  std::cout << "Printing nodes: ..." << std::endl;
   
  cs._printNodes(); 

  return 0;
}
