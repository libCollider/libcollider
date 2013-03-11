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
    
        /// Default Constructor 
        Node();
  
        /// Create a Node with a user defined name and Id
        /// @param[in] const std::string& Name
        /// @param[in] int Id        
	Node(const std::string& defName, int id);
 
        /// Destructor
        ~Node();
   
        /// Returns the Id of this Node
        /// @returns _id
        int _getId() const {return _id;}

        /// Command the server to run this Node
	void _run(Client_Server &cs); //mod running flag
    
        /// Command the server to stop this Node
	void _stop(Client_Server &cs); //mod running flag
     
        /// Command the server to free this Node
        void _free(Client_Server &cs); //add check for running

        /// Returns true if this Node is currently playing, else false
        /// @returns true if currently playing, else false
   	bool _isPlaying()  {return _playing;}  //fix me
  
        /// Returns true if this Node is currently running, else false
        /// @returns true if currently running, else false
   	bool _isRunning()  {return _running;}	//fix me
  
        /// Returns the name of this Node
        /// @returns _defName
        std::string _getDefName() const {return _defName;}
  
        /// Query the server for this Node
        void _query(Client_Server &cs);

        // @{
        /// @name Control and Bus Mapping Functions
   
        /// Set this Node with specified control values 
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] std::map<std::string, float>& Control Values
        void _set(Client_Server &cs, std::map<std::string, float> &controlVals);
     
        /// Set this Node with specified control range values 
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] std::map<std::string, float[]>& Control Ranges
        void _setn(Client_Server &cs, std::map<std::string, float[]> &controlRanges);

        /// Set this Node with specified bus mappings
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] std::map<std::string, Bus>& map
        void _busMap(Client_Server &cs, std::map<std::string, Bus> &map);
        // @}

        //TO_DO
        //Node controls - control value ranges, fill ranges, map controls to read from bus(es),
	//Node placement 
	//Node query
	//Trace

   protected:
   	int _id;
        std::string _defName;
        bool _playing;
        bool _running;
   private:
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
	Synth(Client_Server &cs, const std::string& defName, int id,
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
	Synth(Client_Server &cs, const std::string& defName, 
			int id, std::map<std::string,float> &args,
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
	Group(Client_Server &cs, const std::string& name, int id, 
				int addAction = TO_HEAD, int target = DEFAULT_GROUP);
  
        /// Destructor
        ~Group();

        /// Free all Nodes in this Group
        /// @param[in] Client_Server& Client_Server instance
        void _freeAllSynths(Client_Server &cs);
    
        /// Free all Nodes in this Group and in all Sub-Groups
        /// @param[in] Client_Server& Client_Server instance
        void _deepFreeAllSynths(Client_Server &cs);

   private:
 };

 /// This class represents a client-side version of a server root node
 class RootNode: public Group
 {
   public:

        /// Create a Root Node
        /// @param[in] Client_Server& Client_Server instance
	RootNode(Client_Server &cs);
   
        /// Destructor
	~RootNode();
   private:
 };
} //namespace ColliderPlusPlus
#endif

