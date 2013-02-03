#ifndef OSC_MESSENGER
#define OSC_MESSENGER


#include <string>
namespace ColliderPlusPlus {

 class OscMessenger
 {
  public:
        OscMessenger();
        ~OscMessenger();
        void _createSynth(std::string name, int nodeID, int pauseTime);
        void _killSynth(int nodeID, int pauseTime); 
        void _killServer(int pauseTime);
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
