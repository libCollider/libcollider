/// @file Node.hpp
/// @brief Header file for Node.hpp
/// @author Eric Hamdan erichamdan@gmail.com
#ifndef NODE
#define NODE

#include "Client_Server.hpp"
#include "Bus.hpp"
#include <string>
#include <map>

namespace ColliderPlusPlus {

 /// This class represents a client-side version of a server node (Synth or Group)
 class Node 
 {
   public:
      
        /// Create a Node with a user defined name and Id
        /// @param[in] const std::string& Name
        /// @param[in] int Id        
	Node(Client_Server * other, const std::string& defName, int id_);
 
        /// Destructor
        ~Node();
   
        /// Returns the Id of this Node
        /// @returns id
        int getId() const {return id;}

        /// Command the server to run this Node
	void run(); //mod running flag
    
        /// Command the server to stop this Node
	void stop(); //mod running flag
     
        /// Command the server to free this Node
        void free(); //add check for running

        /// Returns true if this Node is currently playing, else false
        /// @returns true if currently playing, else false
   	bool isPlaying() const {return playing;}  //fix me
  
        /// Returns true if this Node is currently running, else false
        /// @returns true if currently running, else false
   	bool isRunning() const {return running;}	//fix me

        /// Returns true if the Node was freed from the server by 
        /// calling free() BEFORE the destructor of this Node is called
        /// @returns true if freed from server with free() prior to destruction 
        bool getManuallyFreed() const {return manuallyFreed;}
  
        /// Returns the name of this Node
        /// @returns defName
        std::string getDefName() const {return defName;}

        /// Return this Node's Client_Server pointer
        /// @returns cs
        Client_Server* getClientServer() const {return cs;};
  
        /// Query the server for this Node
        void query();

        // @{
        /// @name Control and Bus Mapping Functions
   
        /// Set this Node with specified control values 
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] std::map<std::string, float>& Control Values
        void set(std::map<std::string, float> &controlVals);
     
        /// Set this Node with specified control range values 
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] std::map<std::string, float[]>& Control Ranges
        void setn(std::map<std::string, float[]> &controlRanges);

        /// Set this Node with specified bus mappings
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] std::map<std::string, Bus>& map
        void busMap(std::map<std::string, Bus> &map);
        // @}

        //TO_DO
        //Node controls - control value ranges, fill ranges, map controls to read from bus(es),
	//Node placement 
	//Node query
	//Trace
   	
   private:
	int id;
        std::string defName;
        bool playing;
        bool running;
        bool manuallyFreed;

        Client_Server * cs;
 };

 /// This class represents a client-side version of a server synth
 class Synth: public Node
 {
   public:
       
        /// Create a Synth with a user defined name, id, addAction, and target
        /// If no addAction is specified, this Synth is added to the head of target group
        /// If no target group is specified, this Synth is added to the Default Group
        /// @param[in] Client_Server& Client_Server instance
	/// @param[in] const std::string& defName
        /// @param[in] int Id
	/// @param[in] int Add Action
        /// @param[in] int Target Group
	Synth(Client_Server * other, const std::string& defName, 
		 int id_, int initAction = 0, 
			       int addAction = TO_HEAD, int target = DEFAULT_GROUP);
  
        /// Create a Synth with a user defined name, id, Node args, addAction, and target
        /// If no addAction is specified, this Synth is added to the head of target group
        /// If no target group is specified, this Synth is added to the Default Group
        /// @param[in] Client_Server& Client_Server instance
	/// @param[in] const std::string& defName
        /// @param[in] int Id
        /// @param[in] std::map<std::string, float> Args
	/// @param[in] int Add Action
        /// @param[in] int Target Group
	Synth(Client_Server * other, const std::string& defName, 
		 int id_, std::map<std::string,float> &args, int initAction = 0,
		                int addAction = TO_HEAD, int target = DEFAULT_GROUP);
  
        /// Destructor
	~Synth();
   private:
 };

 /// This class represents a client-side version of a server group
 class Group: public Node
 {
   public:

        /// Create a Group with a user defined name, id, addAction, and target
        /// If no addAction is specified, this Group is added to the head of target group
        /// If no target group is specified, this Synth is added to the Default Group
        /// @param[in] Client_Server& Client_Server instance
	/// @param[in] const std::string& Name
        /// @param[in] int Id
	/// @param[in] int Add Action
        /// @param[in] int Target Group
	Group(Client_Server * other, const std::string& name, int id_, 
				int addAction = TO_HEAD, int target = DEFAULT_GROUP);
  
        /// Destructor
        ~Group();

        /// Free all Nodes in this Group
        /// @param[in] Client_Server& Client_Server instance
        void freeAllSynths();
    
        /// Free all Nodes in this Group and in all Sub-Groups
        /// @param[in] Client_Server& Client_Server instance
        void deepFreeAllSynths();

   private:
 };

 /// This class represents a client-side version of a server root node
 class RootNode: public Group
 {
   public:

        /// Create a Root Node
        /// @param[in] Client_Server& Client_Server instance
	RootNode(Client_Server * other);
   
        /// Destructor
	~RootNode();
   private:
 };
} //namespace ColliderPlusPlus
#endif

