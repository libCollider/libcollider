#include "Buffer.hpp"



using namespace ColliderPlusPlus;

Buffer::Buffer()
:_bufNum(0), _numFrames(0), _numChans(0), _sampRate(44100), _filePath("")
{


}

Buffer::~Buffer()
{


}

void Buffer::_alloc(Client_Server &cs, int numFrames, int numChans, int bufNum)
{
  _numFrames = numFrames;
  _numChans = numChans;
  _bufNum = bufNum;
  cs._allocBuffer(_numFrames, _numChans, _bufNum);
}
