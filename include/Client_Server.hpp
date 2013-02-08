#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include "OscMessenger.hpp"
#include "Node.hpp"
#include <string>
#include <vector> 


//Client-side representation of a scsynth server instance

namespace ColliderPlusPlus {

  class Client_Server
  {
    public:

        friend class Node;

        Client_Server();
      	Client_Server(const std::string name);
        Client_Server(const std::string name, const char *host, const char *port);
      	~Client_Server();
        std::string _getName();
        OscMessenger& _getOscMessenger();
  
        /** System Server Commands **/
      	//boot scsynth and create default group
        void _boot();
        int _nextNodeId();
        bool _pingScsynth();
        void _dumpOSC(int toggle);
        void _printCurrentNodeIds();
        void _queryNodeTree();

        /** OSC/UDP 		   **/
        void _setPort(const char *port);
        void _setHost(const char *host);
        const char* _getPort();
        const char* _getHost();
	
        /** Synth Commands         **/
        bool _loadSynthDef(std::string synthDefName);
	bool _loadSynthDefDirectory(std::string dirName); //optional bytes, see osc command ref

    protected:
       	static bool _createNode(int nodeId);
     	static bool _createSynth(std::string name, int nodeId);
        static bool _createGroup(std::string name, int nodeId);
	static bool _runNode(int nodeId, int flag);
        static bool _freeNode(int nodeID);
         
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
