#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include <string>
#include <vector> 
#include <map>

//addAction Macros 
#define TO_HEAD      0
#define TO_TAIL      1
#define JUST_BEFORE  2
#define JUST_AFTER   3
#define REPLACE      4

#define ROOT_NODE     0
#define DEFAULT_GROUP 1

#define SYNTH 1
#define GROUP 2


//Client-side representation of a scsynth server instance

namespace ColliderPlusPlus {

  class Client_Server
  {
    public:

        Client_Server();
      	Client_Server(const std::string& name);
        Client_Server(const std::string& name, const char *host, const char *port);
      	~Client_Server();
        
        /** System Server Commands **/
	std::string _getName();
        void _boot();
        int _nextNodeId();
	bool _dumpOSC(int toggle);
	void _printCurrentNodeIds();
	void _queryNodeTree();
        bool _pingScsynth();
	bool _quit();
       
        /** Node Commands         **/
        bool _loadSynthDef(const std::string& synthDefName);
	bool _loadSynthDefDirectory(const std::string& dirName); //optional bytes, see osc command ref
	bool _createNode(int nodeId, int addAction = TO_HEAD, 
					    int target = DEFAULT_GROUP, int type = SYNTH);

	bool _createNode(const std::string& name, int nodeId,
				     int addAction = TO_HEAD, 
					    int target = DEFAULT_GROUP, int type = SYNTH);

     	bool _createSynth(const std::string& name, int nodeId,
			             int addAction = TO_HEAD, int target = DEFAULT_GROUP);

	bool _createSynth(const std::string& name, int nodeId, 
			        std::map<std::string, float> &args, 
			              int addAction = TO_HEAD,int target = DEFAULT_GROUP);

	bool _createGroup(int nodeId, int addAction = TO_HEAD, int target = DEFAULT_GROUP);

	bool _runNode(int nodeId, int flag);
        bool _freeNode(int nodeID);

        /** Synth Definitions **/
//	bool _synthDef(const string& name, const char* argv[]);
    	 
    private:
        //Methods
        bool _createDefaultGroup();
	int _pushFirstNodeId(int nextNode);

	/**      OSC/UDP     **/
	void _setPort(const char *port);
        void _setHost(const char *host);
        const char* _getPort();
        const char* _getHost();

	//Members
        std::string _name;
	const char* _port;
        const char* _host;
        int _nextNode;
	std::vector<int> _nodeIDs;	
  };
} //namespace ColliderPlusPlus
#endif
