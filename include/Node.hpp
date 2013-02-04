#ifndef NODE
#define NODE

#include <string>

namespace ColliderPlusPlus {

 class Node 
 {
   public:
        Node(int id);
	virtual ~Node();
        int _getId() const {return _id;}
   	bool _isPlaying()  {return _playing;}  
   	bool _isRunning()  {return _running;}	
   private:
   	int _id;
        bool _playing;
        bool _running;
	//Client_Server* cs; instance of server
	//instance of group? how to implement? container, class?
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
	virtual ~Group();

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

