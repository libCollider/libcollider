/// @file Client_Server.hpp
/// @brief Header file for Client_Server.hpp
/// @author Eric Hamdan erichamdan@gmail.com 
#ifndef CLIENT_SERVER
#define CLIENT_SERVER

#include <string>
#include <vector> 
#include <map>
#include "tny_osc/tnyosc-dispatch.hpp"
#include "tny_osc/tnyosc.hpp"
 
#define TO_HEAD      0
#define TO_TAIL      1
#define JUST_BEFORE  2
#define JUST_AFTER   3
#define REPLACE      4

#define ROOT_NODE     0
#define DEFAULT_GROUP 1

#define SYNTH 1
#define GROUP 2

namespace ColliderPlusPlus {

  /// This class represents a client-side version of scsynth, the SuperCollider audio server
  class Client_Server
  {
    public:

        /// Create a default Client_Server. 
        Client_Server();

        /// Create a Client_Server with a user defined name, host address, port,
        /// and specific scsyndef directory to load upon instantiation
        /// @param[in] const std::string& Name
        /// @param[in] const char *host
        /// @param[in] const char *port
        /// @param[in] cont std::string& SynthDef Directory
        Client_Server(const std::string& name, const char *host,
			     const char *port, const std::string& synthDefDir);
        
        /// Destructor
      	~Client_Server();
        
      	// @{
        /// @name General System Functions

        /// Returns this Client_Server's user defined name as a std:string
        /// @return This Client_Server's name as a std::string
        std::string getName() const { return name;}

        /// Returns a unique Node id (int) starting from 1000
        /// @returns A unique Node id (int)
        int nextNodeId();

        /// Returns a unique Buffer number (int) starting from 0
        /// @returns A unique Buffer number (int)
	int nextBufferNum();
 
        /// Command the server to dump all incoming OSC messages
        /// @param[in] int 0->OFF 1->ON
	void dumpOSC(int toggle);

        /// Print current Node ids associated with this instance
	void printCurrentNodeIds();
  
        /// Command server to print current Node tree
	void queryNodeTree();
   
        /// Query a specific node for its info on the server
	void queryNode(int nodeId);

        /// Send /status command to server, replies with /status_info
        void status();

        /// Command the server to quit 
	void quit();
        // @}
       
        // @{
	/// @name Node Functions

        /// Returns true if the specified scsyndef path was successfully
        /// loaded by scsynth, false if failed
        /// @return true if success, else false
        bool loadSynthDef(const std::string& synthDefName);

        /// Returns true if the specified scsyndef directory path was successfully
        /// loaded by scsynth, false if failed
        /// @return true if success, else false
	bool loadSynthDefDirectory(const std::string& synthDefDir); 

        /// Command the server to create a new "default" Node 
	/// @param[in] int Node Id
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	/// @param[in] int Type (Synth or Group)
	void createNode(int nodeId, int addAction = TO_HEAD, 
					     int target = DEFAULT_GROUP, int type = SYNTH);

        /// Command the server to create a new Node specified by the Name parameter
        /// @param[in] std::string Name
	/// @param[in] int Node Id
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	/// @param[in] int Type (Synth or Group)
	void createNode(const std::string& name, int nodeId,
				     int addAction = TO_HEAD, 
					     int target = DEFAULT_GROUP, int type = SYNTH);

        /// Command the server to create a new Synth specified by the Name parameter
        /// @param[in] std::string Name
	/// @param[in] int Node Id
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	/// @param[in] int Type (Synth or Group)
     	void createSynth(const std::string& name, int nodeId,
			              int addAction = TO_HEAD, int target = DEFAULT_GROUP);

        /// Command the server to create a new PAUSED Synth specified by the Name parameter
        /// @param[in] std::string Name
	/// @param[in] int Node Id
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	/// @param[in] int Type (Synth or Group)
     	void createPausedSynth(const std::string& name, int nodeId,
			              int addAction = TO_HEAD, int target = DEFAULT_GROUP);

        /// Command the server to create a new Synth specified by the Name parameter 
        /// with user specified arguments
        /// @param[in] std::string Name
	/// @param[in] int Node Id
        /// @param[in] std::map<std::string, float> Args
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	/// @param[in] int Type (Synth or Group)
	void createSynth(const std::string& name, int nodeId, 
			        std::map<std::string, float> &args, 
			               int addAction = TO_HEAD,int target = DEFAULT_GROUP);

        /// Command the server to create a new PAUSED Synth specified by the Name parameter 
        /// with user specified arguments
        /// @param[in] std::string Name
	/// @param[in] int Node Id
        /// @param[in] std::map<std::string, float> Args
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	/// @param[in] int Type (Synth or Group)
	void createPausedSynth(const std::string& name, int nodeId, 
			        std::map<std::string, float> &args, 
			               int addAction = TO_HEAD,int target = DEFAULT_GROUP);

        /// Command the server to create a new Group
	/// @param[in] int Node Id
        /// @param[in] int Add Action
	/// @param[in] int Target Group
	void createGroup(int nodeId, int addAction = TO_HEAD, int target = DEFAULT_GROUP);

        /// Command the server to run the Node specified by the nodeId parameter
        /// 0 stops and 1 starts
	/// @param[in] int Node Id 
	/// @param[in] int Flag 0->Stop 1->Start
	void runNode(int nodeId, int flag);

        /// Command the server to free the Node specified by the nodeId parameter
        /// @param[in] int Node Id
        void freeNode(int nodeID);
  
        /// Commmand the server to set the Node specified by the nodeId parameter
        /// with arguments specified by the std::map parameter
        /// @param[in] int Node Id
        /// @param[in] std::map<std::string, float> Control Values
        void setNodeControls(int nodeId, std::map<std::string, float> &controlVals);
        /*void _setNodeControlRanges(int nodeId, 
					std::map<std::string, float []> &controlRanges);*/

        /// Command the server to free all the Nodes in the Group specified by the groupId
        /// parameter
        /// @param[in] int Group Id
        void freeAllSynths(int groupId);
  
        /// Command the server to free all Nodes in the Group specified by the groupId
        /// parameter and all Nodes in any existing sub-groups  
        void deepFreeAllSynths(int groupId); 
	// @}


        // @{
	/// @name Buffer Functions

        /// Returns true if buffer allocation was successful, else false
        /// @param[in] int Buffer Number
	/// @param[in] int Number of Sample Frames
        /// @param[in] int Number of Channels
        /// @returns true if success, else false
        bool allocBuffer(int bufNum, int numFrames, int numChans);
 
        /// Returns true if buffer was freed successfully, else false
        /// @param[in] int Buffer Number
        /// @returns true if success, else false
	bool freeBuffer(int bufNum);

        void freeBuffer_no_reply(int bufNum);
  
        /// Return true if buffer allocation and soundfile read was successful, else false
        /// @param[in] int Buffer Number
        /// @param[in] const std::string& Full Soundfile Path
        /// @param[in] int Starting Sample Frame
        /// @param[in] int Number of Frames, -1 loads all frames in file
        /// @returns true if success, else false
        bool allocReadBuffer(int bufNum,
				    const std::string& filePath,
					 int startFileFrame = 0, 
					       int numFrames = -1);
        
        /// Query a Buffer specified by the Buffer number
        /// @param[in] int Buffer Number 
        void queryBuffer(int bufNum);
 
        /// Add a pointer to a Buffer instance to the _buffers vector 
        /// @param[in] void * buffer
        void addBuffer(void* buffer);
        // @}

    private:
        //Functions
        void createDefaultGroup();
        void initializeSynthDefs(const std::string& synthDefDir);
        void setUpOSCDispatcher();
        void send_msg_with_reply(tnyosc::Message * msg, const char * send_msg = NULL);
        void send_msg_no_reply(tnyosc::Message * msg, const char * send_msg = NULL);	
        void send_bundle_with_reply(tnyosc::Bundle * bundle, const char * send_msg = NULL);
        void send_bundle_no_reply(tnyosc::Bundle * bundle, const char * send_msg = NULL);

	//OSC/UDP
	void setPort(const char *port);
        void setHost(const char *host);
        const char* getPort();
        const char* getHost();

        std::string name;
	const char* port;
        const char* host;
      	std::vector<int> nodeIDs;
        std::map<int, void*> buffers;
        tnyosc::Dispatcher dispatcher;	
        bool async_result;
        int NodeIDGenerator;
        int BufferIDGenerator;
  };
} //namespace ColliderPlusPlus
#endif
