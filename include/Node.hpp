#ifndef NODE
#define NODE

#include "Client_Server.hpp"
#include "Bus.hpp"
#include <string>
#include <map>

namespace ColliderPlusPlus {

 class Node 
 {
   public:
        Node();
	Node(const std::string& defName, int id);
        ~Node();
        int _getId() const {return _id;}
	void _run(Client_Server &cs); //mod running flag
	void _stop(Client_Server &cs); //mod running flag
        void _free(Client_Server &cs); //add check for running
   	bool _isPlaying()  {return _playing;}  //fix me
   	bool _isRunning()  {return _running;}	//fix me
        std::string _getDefName() const {return _defName;}
        void _query(Client_Server &cs);

        void _set(Client_Server &cs, std::map<std::string, float> &controlVals);
        void _setn(Client_Server &cs, std::map<std::string, float[]> &controlRanges);
        void _busMap(Client_Server &cs, std::map<std::string, Bus> &map);
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
	Synth(Client_Server &cs, const std::string& defName, int id,
				int addAction = TO_HEAD, int target = DEFAULT_GROUP);
	Synth(Client_Server &cs, const std::string& defName, 
			int id, std::map<std::string,float> &args,
				int addAction = TO_HEAD, int target = DEFAULT_GROUP);
	~Synth();
   private:
 };

 class Group: public Node
 {
   public:
	Group(Client_Server &cs, const std::string& name, int id, 
				int addAction = TO_HEAD, int target = DEFAULT_GROUP);
        ~Group();

        void _freeAllSynths(Client_Server &cs);
        void _deepFreeAllSynths(Client_Server &cs);

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

