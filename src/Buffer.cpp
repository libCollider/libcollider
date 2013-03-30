#include "Buffer.hpp"
#include <stdlib.h>

using namespace ColliderPlusPlus;

Buffer::Buffer(Client_Server * cs)
:_numFrames(0), _numChans(0),
 _sampRate(44100), _manuallyFreed(false)
{
  _cs = cs;
  _bufNum = _cs->_nextBufferNum();
  _cs->_add_buffer(this);
}

Buffer::~Buffer()
{
  if(_manuallyFreed != true)
 	_cs->_freeBuffer_no_reply(_bufNum);
}

void Buffer::_alloc(int numFrames, int numChans)
{
  _numFrames = numFrames;
  _numChans = numChans;

  if(!_cs->_allocBuffer(_bufNum, _numFrames, _numChans))
	exit(0);

  #ifdef PRINT_DEBUG
  std::cout << "\nsyncing buffer # " << _bufNum << std::endl;
  #endif
  _sync(); 
}

void Buffer::_free()
{
  if(!_cs->_freeBuffer(_bufNum))
 	exit(0);
  else
  	_manuallyFreed = true;  
}

void Buffer::_sync()
{
  _cs->_queryBuffer(_bufNum);
}

void Buffer::_allocRead(const std::string& filePath, int startFileFrame, 
				int numFrames)
{ 
  if(!_cs->_allocReadBuffer(_bufNum, filePath, startFileFrame, numFrames))
  {
    exit(0);
  } 

  #ifdef PRINT_DEBUG
  std::cout << "\nsyncing buffer # " << _bufNum << std::endl;
  #endif
  _sync();
}
