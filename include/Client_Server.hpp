#ifndef CLIENT_SERVER
#define CLIENT_SERVER

//#include "OscMessenger.hpp"
#include <string>
#include <vector> 


//Client-side representation of a scsynth server instance

namespace ColliderPlusPlus {

  class Client_Server
  {
    public:

        friend class Node;
        friend class Synth;

        Client_Server();
      	Client_Server(const std::string& name);
        Client_Server(const std::string& name, const char *host, const char *port);
      	~Client_Server();
        std::string _getName();
      //  OscMessenger& _getOscMessenger();
  
        /** System Server Commands **/
      	//boot scsynth and create default group
        void _boot();
        int _nextNodeId();
        bool _pingScsynth();
	void _quitServer();
        void _dumpOSC(int toggle);
        void _printCurrentNodeIds();
        void _queryNodeTree();

        /** OSC/UDP 		   **/
        void _setPort(const char *port);
        void _setHost(const char *host);
        static const char* _getPort();
        static const char* _getHost();
	
        /** Synth Commands         **/
        bool _loadSynthDef(const std::string& synthDefName);
	bool _loadSynthDefDirectory(const std::string& dirName); //optional bytes, see osc command ref

    protected:
       	static bool _createNode(int nodeId);
     	static bool _createSynth(const std::string& name, int nodeId);
       // static bool _createGroup(std::string& name, int nodeId);
	static bool _runNode(int nodeId, int flag);
        static bool _freeNode(int nodeID);
        
         
    private:
        //Methods
        int _pushFirstNodeId(int nextNode);
        void _createDefaultGroup();

	//Members
 	//static OscMessenger _oscm;
        std::string _name;
        int _nextNode;
	std::vector<int> _nodeIDs;
        const char* _port;
        const char* _host;	
  };
  
  
} //namespace ColliderPlusPlus
#endif
