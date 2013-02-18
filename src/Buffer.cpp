#include "Buffer.hpp"
#include <iostream>
#include <stdlib.h>

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
  if(!cs._allocBuffer(_bufNum, _numFrames, _numChans))
	exit(0);

  _numFrames = numFrames;
  _numChans = numChans;  
}

void Buffer::_free(Client_Server &cs)
{
  if(!cs._freeBuffer(_bufNum))
 	exit(0);
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
