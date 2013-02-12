#ifndef NODE
#define NODE

#include <string>
#include "Client_Server.hpp"


namespace ColliderPlusPlus {

 class Node 
 {
   public:
        //Node();
        Node(Client_Server &cs, int id, int type);
	Node(Client_Server &cs, const std::string& defName, int id, int type);
        virtual ~Node();
        int _getId() const {return _id;}
	bool _run(Client_Server &cs);
	bool _stop(Client_Server &cs);
        bool _free(Client_Server &cs);
   	bool _isPlaying()  {return _playing;}  
   	bool _isRunning()  {return _running;}	
        std::string _getDefName() const {return _defName;}

        // TO_DO
        //Node controls - set control value, control value ranges, fill ranges, map controls to read from bus(es),
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

 class Synth: public Node
 {
   public:
	Synth(Client_Server &cs, const std::string& defName, int id);
	~Synth();
   private:
 };

 class Group: public Node
 {
   public:
	Group(Client_Server &cs, const std::string& name, int id);
        ~Group();

   private:
 };

 class RootNode: public Group
 {
   public:
	RootNode(Client_Server &cs);
	~RootNode();
   private:
 };
} //namespace ColliderPlusPlus
#endif

