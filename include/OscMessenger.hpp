#ifndef OSC_MESSENGER
#define OSC_MESSENGER


#include <string>
namespace ColliderPlusPlus {

 class OscMessenger
 {
  public:
        OscMessenger();
        ~OscMessenger();
       // void _sendMsg(
        void _dumpOSC(int toggle);
        void _createNode(std::string name, int nodeID, int pauseTime);
        void _freeNode(int nodeID, int pauseTime); 
        void _killServer(int pauseTime);
        void _queryNodeTree();
   
        void _loadSynthDef(std::string synthDefName);
        void _loadSynthDefDirectory(std::string dirName); //optional bytes param, see osc command ref

        void _setPort(const char *port);
        void _setHost(const char *host);
        const char* _getPort();
        const char* _getHost();
  private:
	const char* _port;
        const char* _host;
 };
} //namespace ColliderPlusPlus
#endif
