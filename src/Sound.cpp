#include "Sound.hpp"
#include "unistd.h"

using namespace sc;

Sound::Sound(SCServer * cs, const std::string &filepath, int outarray [], int ia)
:_isValid(false), _isLooping(false), _isPlaying(false), _gain(1), _pitchScalar(1), _initAction(ia),
 _startPos(0.0f), _rateScalar(1.0f) 
{
  init(cs, filepath, outarray, _initAction);  
}

Sound::~Sound()
{
  if(buffer)
    delete buffer;
  if(synth)
    delete synth;
}
void Sound::init(SCServer * other, const std::string &filepath, int outarray [], int _initAction)
{
  cs = other;
  buffer = new Buffer(cs, cs->nextBufferNum());

  if(buffer == NULL) 
  {
     _isValid = false;	
  }
  else 
  {
     if(!(buffer->allocRead(filepath)))
     {
        std::cerr << "Error allocating buffer resources on server." << std::endl;
        _isValid = false;
     }
     else 
     {
        args["bufnum"] = buffer->getBufNum();
        args["rate"] = _pitchScalar;
        args["looping"] = 0;
        args["amp"] = 1;
  
        if(buffer->getChanNum() == 2) {
	  // std::cerr << "...creating 2ch sound player" << std::endl;
	   args["outpos1"] = outarray[0];
 	   args["outpos2"] = outarray[1];
           synth = new Synth(cs, "SoundFile_Loop_Stereo", cs->nextNodeId(), args, _initAction);}
        else if (buffer->getChanNum() == 1) {
          // std::cerr << "...creating 1ch sound player" << std::endl;
	   args["outpos1"] = outarray[0];
           synth = new Synth(cs, "SoundFile_Loop_Mono", cs->nextNodeId(), args, _initAction);} 
        else 
	   _isValid = false;

        if(synth == NULL)
	   _isValid = false;
	else 
        {
           _isValid = true; 
        }
     }
   }  
}

void Sound::play()
{
  synth->run();
  _isPlaying = true; 
}

void Sound::pause()
{
  synth->pause();
  _isPlaying = false;
}

void Sound::jumpToStartPos()
{
  if(args["trig"] == 1)
  {
	args["trig"] = -1;
	synth->set(args);	
	usleep(20000);
	args["trig"] = 1;
	synth->set(args);
  }
  
  else
  {
        args["trig"] = 1;
        synth->set(args);
  }
}

void Sound::setStartPosition(float pos)
{
  _startPos = pos;
  args["startpos"] = _startPos;
  synth->set(args);
}

void Sound::setGain(float gain)
{
  _gain = gain;
  args["amp"] = _gain;
  synth->set(args);
}

void Sound::setRate(float rateScalar)
{
  _rateScalar = rateScalar;
  args["rate"] = _rateScalar;
  synth->set(args);
}

int Sound::setLoop(bool loop)
{
  if(_isLooping == loop)
    return 1;

  if(loop == true) {
    args["looping"] = 1;
    synth->set(args);
    _isLooping = loop;
    return 0;
  }

  else if(loop == false) {
    args["looping"] = 0;
    synth->set(args);
    _isLooping = loop;
    return 0;
  }

  return 1;
}

   
