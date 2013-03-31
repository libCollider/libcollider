#include "Sound.hpp"

using namespace ColliderPlusPlus;

Sound::Sound(Client_Server * cs, const std::string &filepath, int ia)
: isLooping(false), isPlaying(false), gain(1), pitchScalar(1) 
{
  initAction = ia;
  init(cs, filepath, initAction);  
}

Sound::~Sound()
{
  if(buffer)
    delete buffer;
  if(synth)
    delete synth;
}

void Sound::init(Client_Server * cs, const std::string &filepath, int initAction)
{
  cs = cs;
  buffer = new Buffer(cs, cs->nextBufferNum());
  buffer->allocRead(filepath);
  args["bufnum"] = buffer->getBufNum();
  args["rate"] = pitchScalar;
  args["looping"] = 0;
  
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

int Sound::loop(bool loop)
{
  if(isLooping == loop)
    return 1;

  isLooping = loop;

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

   
