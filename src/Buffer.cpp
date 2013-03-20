#include "Buffer.hpp"
#include <iostream>
#include <stdlib.h>

using namespace ColliderPlusPlus;

Buffer::Buffer()
{

}

Buffer::Buffer(Client_Server * cs, int bufNum)
:_bufNum(bufNum), _numFrames(0), _numChans(0),
 _sampRate(44100), _filePath(""), _manuallyFreed(false)
{
  _cs = cs;
}

Buffer::~Buffer()
{
  if(_getManuallyFreed() != true)
 	_free();
}

void Buffer::_alloc(int numFrames, int numChans)
{
  if(!_cs->_allocBuffer(_bufNum, _numFrames, _numChans))
	exit(0);

  _numFrames = numFrames;
  _numChans = numChans;  
}

void Buffer::_free()
{
  if(!_cs->_freeBuffer(_bufNum))
 	exit(0);
  else
  	_manuallyFreed = true;  
}

void Buffer::_query()
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
}
