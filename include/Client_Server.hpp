#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include "OscMessenger.hpp"
#include <string>
#include <vector> 


//Client-side representation of a scsynth server instance

namespace ColliderPlusPlus {

  class Client_Server
  {
    public:

        //Default Constructor with name "Default Client Server"
        Client_Server();
  
        //Constructor for a Client_Server with a user defined name
	Client_Server(const std::string name);
   
        //Destructor
	~Client_Server();

        //Return this Client_Server's OscMessenger
        OscMessenger& _getOscMessenger();

        //Ping an scsynth instance to connect
        bool _pingScsynth();

        //Return calling Client_Server's name
        std::string _getName();

        //First id returned is default group id = 1
        int _nextNodeID();

        //Print current nodes
        void _printNodes();
    private:
 	OscMessenger _oscm;
        std::string _name;
        int _nextNode;
	std::vector<int> _nodeIDs;	
  };
} //namespace ColliderPlusPlus
#endif
