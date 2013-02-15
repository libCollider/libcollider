#ifndef BUFFER
#define BUFFER

#include "Client_Server.hpp"
#include <string>

namespace ColliderPlusPlus {

  class Buffer
  {
    public:
	Buffer();
        ~Buffer();
        int _getBufNum() const {return _bufNum;} //return id of server-side buffer
	int _getFrameNum() const {return _numFrames;} //return sample frames of server-side buffer
	int _getChanNum() const {return _numChans;}
 	int _getSampRate() const {return _sampRate;}
	const std::string& _getFilePath() const {return _filePath;}

	//use cs._getBufNum() for bufNum arg
        void _alloc(Client_Server &cs, int numFrames, int numChannels, int bufNum);

    private:	
	//members
	int _bufNum;
	int _numFrames;
	int _numChans;
	int _sampRate;
	const std::string _filePath;
  };
} //namespace ColliderPlusPlus

#endif

