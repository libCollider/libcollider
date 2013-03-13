#include "Sound.hpp"

using namespace ColliderPlusPlus

Sound::Sound(const std::string &filepath, const int initAction)
:_isLooping(false), _isPlaying(false) _gain(1), _pitchScalar(1) 
{
  _filepath = filepath;
  _initAction = initAction;
  _init(_filepath);  
}

~Sound::Sound()
{
  if(_cs)
    delete _cs;
 
  if(_buffer)
    delete _buffer;

  if(_synth)
    delete _synth;
}

void Sound::_init(const std::string &filepath)
{
  _cs = new Client_Server("A Server");
  _buffer = new Buffer(_cs.nextBufferNum());
  _buffer->allocRead(_cs, filepath);
  std::map<std::string, float> sArgs;
  args["bufnum"] = _buffer->_getBufNum();
  args["rate"] = _pitchScalar;
  args["looping"] = 0;
  
  //Add conditional based on buffer chanNum that determines 
  //synthdef to be loaded
  _synth(_cs, "SoundFile_Loop_Stereo", _cs._nextNodeId(), sArgs, NEW_PAUSED);
}

void Sound::_play()
{
  _synth->_run(_cs);
}

void Sound::_stop()
{
  _synth->stop(cs);
}

int Sound::_loop(bool loop)
{
  if(_isLooping == loop)
    return 0;

  _isLooping = loop;

  if(loop == true) {
    args["looping"] = 1;
    _synth->set(_cs, args);
    _isLooping = loop;
    return 0;
  }

  else if(loop == false) {
    args["looping"] = 0;
    _synth->set(_cs, args);
    _isLooping = loop;
    return 0;
  }

  return 1;
}

   
