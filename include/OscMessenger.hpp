#ifndef OSC_MESSENGER
#define OSC_MESSENGER


#include <string>

namespace ColliderPlusPlus {

 class OscMessenger
 {
  public:
        OscMessenger();
        ~OscMessenger();
        void _boot();
        void _dumpOSC(int toggle);
        bool _createNode(int nodeId);
	bool _createSynth(const std::string& name, int nodeId);
	//bool _createGroup(const std::string& name, int nodeId);
	bool _runNode(int nodeId, int flag);
        bool _freeNode(int nodeId); 
        void _quitServer();
        void _queryNodeTree();
        
   
        bool _loadSynthDef(const std::string& synthDefName);
        bool _loadSynthDefDirectory(const std::string& dirName); //optional bytes param

        void _setPort(const char *port);
        void _setHost(const char *host);
        const char* _getPort();
        const char* _getHost();
  private:
	const char* _port;
        const char* _host;
	void _createDefaultGroup();
 };
} //namespace ColliderPlusPlus
#endif
