#include "Buffer.hpp"
#include <iostream>

using namespace ColliderPlusPlus;

Buffer::Buffer()
{

}

Buffer::Buffer(int bufNum)
:_bufNum(bufNum), _numFrames(0), _numChans(0), _sampRate(44100), _filePath("")
{


}

Buffer::~Buffer()
{


}

void Buffer::_alloc(Client_Server &cs, int numFrames, int numChans)
{
  _numFrames = numFrames;
  _numChans = numChans;
  cs._allocBuffer(_bufNum, _numFrames, _numChans);
}

void Buffer::_free(Client_Server &cs)
{
  cs._freeBuffer(_bufNum);
}

void Buffer::_query(Client_Server &cs)
{
  cs._queryBuffer(_bufNum);
}

void Buffer::_readSoundFile(Client_Server &cs, const std::string& filePath, int startFileFrame, 
				int numFrames)
{
  
  if(!cs._readSoundIntoBuffer(_bufNum, filePath, startFileFrame, numFrames))
  {
    exit(0);
  } 
}
