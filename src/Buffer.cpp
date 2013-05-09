#include "Buffer.hpp"
#include <stdlib.h>

using namespace sc;

Buffer::Buffer(SCServer * other, int bn)
:bufNum(bn), numFrames(0), numChans(0),
 sampRate(44100), manuallyFreed(false)
{
  cs = other;
  cs->addBuffer(this);
}

Buffer::~Buffer()
{
  if(manuallyFreed != true)
 	cs->freeBuffer_no_reply(bufNum);
        cs->removeBuffer(this);
}

void Buffer::alloc(int nf, int nc)
{
  numFrames = nf;
  numChans = nc;

  if(!cs->allocBuffer(bufNum, numFrames, numChans))
	exit(0);

  #ifdef PRINT_DEBUG
  std::cout << "\nsyncing buffer # " << bufNum << std::endl;
  #endif
  sync(); 
}

void Buffer::free()
{
  if(!cs->freeBuffer(bufNum))
 	exit(0);
  else
  	manuallyFreed = true;  
}

void Buffer::sync()
{
  cs->queryBuffer(bufNum);
}

bool Buffer::allocRead(const std::string& filePath, int startFileFrame, 
				int numFrames)
{ 
  if(!cs->allocReadBuffer(bufNum, filePath, startFileFrame, numFrames))
  {
    return false;
  } 

  #ifdef PRINT_DEBUG
  std::cout << "\nsyncing buffer # " << bufNum << std::endl;
  #endif
  sync();
  return true;
}
