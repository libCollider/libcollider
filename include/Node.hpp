#ifndef NODE
#define NODE

#include <string>
#include "Client_Server.hpp"

namespace ColliderPlusPlus {

 class Node 
 {
   public:
        Node();
        Node(int id);
        virtual ~Node();
        int _getId() const {return _id;}
	bool _run();
	bool _stop();
        bool _free();
   	bool _isPlaying()  {return _playing;}  
   	bool _isRunning()  {return _running;}	


        // TO_DO
        //Node controls - set control value, control value ranges, fill ranges, map controls to read from bus(es),
	//Node placement 
	//Node query
	//Trace
   private:
   	int _id;
        bool _playing;
        bool _running;
 };

 class Synth: public Node
 {
   public:
	Synth(std::string defName, int id);
	~Synth();
	std::string _getDefName() const {return _defName;}
   private:
        std::string _defName;
 };

 class Group: public Node
 {
   public:
	Group(int id);
        ~Group();

   private:
 };

 class RootNode: public Group
 {
   public:
	RootNode();
	~RootNode();
   private:
 };
} //namespace ColliderPlusPlus
#endif

