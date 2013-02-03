#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include "OscMessenger.hpp"
#include <string>


//forwards osc messages, keeps track of IDs for nodes, buses, and buffers

namespace ColliderPlusPlus {

  class Client_Server
  {
    public:
        Client_Server();
	Client_Server(const std::string name);
	~Client_Server();
        OscMessenger& _getOscMessenger();
        bool pingScsynth();
        std::string _getName();
    private:
 	OscMessenger _oscm;
        std::string _name;
//	int _id;
	
        
  };
} //namespace OAS_Collider
#endif
