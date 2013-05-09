#include "Sound.hpp"

using namespace sc;

Sound::Sound(SCServer * cs, const std::string &filepath, int ia)
:_isValid(false), _isLooping(false), _isPlaying(false), gain(1), pitchScalar(1), initAction(ia) 
{
  init(cs, filepath, initAction);  
}

Sound::~Sound()
{
  if(buffer)
    delete buffer;
  if(synth)
    delete synth;
}

bool Sound::init(SCServer * other, const std::string &filepath, int initAction)
{
  cs = other;
  buffer = new Buffer(cs, cs->nextBufferNum());

  if(buffer == NULL) 
  {
     return false;	
  }
  else 
  {
     if(!(buffer->allocRead(filepath)))
     {
        std::cerr << "Error allocating buffer resources on server." << std::endl;
        return false;
     }
     else 
     {
        args["bufnum"] = buffer->getBufNum();
        args["rate"] = pitchScalar;
        args["looping"] = 0;
        args["amp"] = 1;
  
        if(buffer->getChanNum() == 2) {
	  // std::cerr << "...creating 2ch sound player" << std::endl;
           synth = new Synth(cs, "SoundFile_Loop_Stereo", cs->nextNodeId(), args, initAction);}
        else if (buffer->getChanNum() == 1) {
          // std::cerr << "...creating 2ch sound player" << std::endl;
           synth = new Synth(cs, "SoundFile_Loop_Mono", cs->nextNodeId(), args, initAction);} 
        else 
	   return false;

        if(synth == NULL)
	   return false;
	else 
        {
           _isValid = true;
	   return isValid(); 
        }
     }
   }  
}

void Sound::play()
{
  synth->run();
  _isPlaying = true; 
}

void Sound::stop()
{
  synth->stop();
  _isPlaying = false;
}

void Sound::setGain(float gain)
{
  args["amp"] = gain;
  synth->set(args);
}

void Sound::setRate(float rateScalar)
{
  args["rate"] = rateScalar;
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

   
