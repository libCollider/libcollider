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
        Client_Server(const std::string name, const char *host, const char *port);
        //Destructor
	~Client_Server();
        //Return calling Client_Server's name
        std::string _getName();
        //Return this Client_Server's OscMessenger
        OscMessenger& _getOscMessenger();
  
 
        /** System Server Commands **/
        /**                        **/
        //Unique node ids start at 1000
        int _nextNodeID();
        //Ping an scsynth instance to connect
        bool _pingScsynth();
        void _dumpOSC(int toggle);
        //Print current node ids
        void _printCurrentNodeIds();
        //This may replace _printNodes()
        void _queryNodeTree();
        void _createNode(std::string name, int nodeID, int pauseTime);
        void _freeNode(int nodeID, int pauseTime); 
        void _killServer(int pauseTime);
	/**                        **/
	/**                        **/

        /** Synth Commands         **/
        /**                        **/
        //Async
        void _loadSynthDef(std::string synthDefName);
	void _loadSynthDefDirectory(std::string dirName); //optional bytes param, see osc command ref
        


        /** OSC/UDP 		   **/
        /**                        **/
        void _setPort(const char *port);
        void _setHost(const char *host);
        const char* _getPort();
        const char* _getHost();
	/**                        **/
	/**                        **/

    private:
        //Methods
        int _pushFirstNodeId(int nextNode);

	//Members
 	OscMessenger _oscm;
        std::string _name;
        int _nextNode;
	std::vector<int> _nodeIDs;
        const char* _port;
        const char* _host;	
  };
} //namespace ColliderPlusPlus
#endif
