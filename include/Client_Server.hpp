#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include <string>
#include <vector> 


//Client-side representation of a scsynth server instance

namespace ColliderPlusPlus {

  class Client_Server
  {
    public:

        Client_Server();
      	Client_Server(const std::string& name);
        Client_Server(const std::string& name, const char *host, const char *port);
      	~Client_Server();
        std::string _getName();
       
        /** System Server Commands **/
      	//boot scsynth and create default group
        void _boot();
        int _nextNodeId();
	void _dumpOSC(int toggle);
	void _printCurrentNodeIds();
	void _queryNodeTree();
        bool _pingScsynth();
	void _quit();
       
        /** OSC/UDP 		   **/
        void _setPort(const char *port);
        void _setHost(const char *host);
        const char* _getPort();
        const char* _getHost();
	
        /** Node Commands         **/
        bool _loadSynthDef(const std::string& synthDefName);
	bool _loadSynthDefDirectory(const std::string& dirName); //optional bytes, see osc command ref
	bool _createNode(int nodeId, int type);
	bool _createNode(const std::string& name, int nodeId, int type);
     	bool _createSynth(const std::string& name, int nodeId);
	bool _createGroup(const std::string& name, int nodeId);
	bool _runNode(int nodeId, int flag);
        bool _freeNode(int nodeID);
    	 
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
