#include "Client_Server.hpp"
#include <iostream>
#include <unistd.h>

using ColliderPlusPlus::Client_Server;

int main()
{

  std::cout << "Creating a default Client_Server" << std::endl;
  Client_Server cs1;
  std::cout << "The server name is: " << cs1._getName() << std::endl;
  std::cout << "The server host is: " << cs1._getHost() << std::endl;
  std::cout << "The server port is: " << cs1._getPort() << std::endl;


  std::cout << "Creating a Client_Server with name Hello" << std::endl;
  Client_Server cs2("Hello");
  std::cout << "The server name is: " << cs2._getName() << std::endl;
  std::cout << "The server host is: " << cs2._getHost() << std::endl;
  std::cout << "The server port is: " << cs2._getPort() << std::endl;


  std::cout << "Creating a Client_Server with name Hello" 
            << ", host 127.0.0.1 and port 57110" << std::endl;
  Client_Server cs3("Hello", "127.0.0.1", "57110");
  std::cout << "The server name is: " << cs3._getName() << std::endl;
  std::cout << "The server host is: " << cs3._getHost() << std::endl;
  std::cout << "The server port is: " << cs3._getPort() << std::endl;

  

  
  
  std::cout << "cs1 next node id is: " <<cs1._nextNodeID() << std::endl;
  std::cout << "cs1 next node id is: " <<cs1._nextNodeID() << std::endl;

  for (int i = 0; i < 5; ++i)
  {
    cs1._nextNodeID();
  }

  std::cout << "Printing nodes: ..." << std::endl;
   
  cs1._printCurrentNodeIds(); 

  std::cout << "cs3 next node id is: " <<cs3._nextNodeID() << std::endl;
  std::cout << "cs3 next node id is: " <<cs3._nextNodeID() << std::endl;

  cs3._queryNodeTree();

  //cs3._loadSynthDef("/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/default.scsyndef");
  //cs1._loadSynthDefDirectory("/Users/administrator/Documents/gitprojects/ColliderPlusPlus/synthdefs/");
 // cs3._createNode("default", 1000, 0);
 // sleep(3);
 // cs3._freeNode(1000,0);
  cs3._killServer(0);
  

  return 0;
}
