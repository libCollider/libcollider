#include "Sound.hpp"

using namespace ColliderPlusPlus;

Sound::Sound(Client_Server * cs, const std::string &filepath, int initAction)
: _isLooping(false), _isPlaying(false), _gain(1), _pitchScalar(1) 
{
  _filePath = filepath;
  _initAction = initAction;
  _init(cs, _filePath, _initAction);  
}

Sound::~Sound()
{
  if(_buffer)
    delete _buffer;
  if(_synth)
    delete _synth;
}

void Sound::_init(Client_Server * cs, const std::string &filepath, int initAction)
{
  _cs = cs;
  _buffer = new Buffer(_cs, _cs->_nextBufferNum());
  _buffer->_allocRead(filepath);
  args["bufnum"] = _buffer->_getBufNum();
  args["rate"] = _pitchScalar;
  args["looping"] = 0;
  
  //Add conditional based on buffer chanNum that determines 
  //synthdef to be loaded
  _synth = new Synth(_cs, "SoundFile_Loop_Stereo", _cs->_nextNodeId(), args, initAction);
}

void Sound::_play()
{
  _synth->_run();
}

void Sound::_stop()
{
  _synth->_stop();
}

int Sound::_loop(bool loop)
{
  if(_isLooping == loop)
    return 1;

  _isLooping = loop;

  if(loop == true) {
    args["looping"] = 1;
    _synth->_set(args);
    _isLooping = loop;
    return 0;
  }

  else if(loop == false) {
    args["looping"] = 0;
    _synth->_set(args);
    _isLooping = loop;
    return 0;
  }

  return 1;
}

   
