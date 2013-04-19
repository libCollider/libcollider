#include "Sound.hpp"

using namespace sc;

Sound::Sound(SCServer * cs, const std::string &filepath, int ia)
: isLooping(false), isPlaying(false), gain(1), pitchScalar(1), initAction(ia) 
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

void Sound::init(SCServer * other, const std::string &filepath, int initAction)
{
  cs = other;
  buffer = new Buffer(cs, cs->nextBufferNum());
  buffer->allocRead(filepath);
  args["bufnum"] = buffer->getBufNum();
  args["rate"] = pitchScalar;
  args["looping"] = 0;
  args["amp"] = 1;
  
  if(buffer->getChanNum() == 2)
     synth = new Synth(cs, "SoundFile_Loop_Stereo", cs->nextNodeId(), args, initAction);
  else
     synth = new Synth(cs, "SoundFile_Loop_Mono", cs->nextNodeId(), args, initAction);
}

void Sound::play()
{
  synth->run();
}

void Sound::stop()
{
  synth->stop();
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
  if(isLooping == loop)
    return 1;

  if(loop == true) {
    args["looping"] = 1;
    synth->set(args);
    isLooping = loop;
    return 0;
  }

  else if(loop == false) {
    args["looping"] = 0;
    synth->set(args);
    isLooping = loop;
    return 0;
  }

  return 1;
}

   
