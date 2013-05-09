#include "libcollider/libcollider.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace sc;

bool init(int argc, char* argv[], const char* &host, const char* &port,
			 std::string &soundfile, std::string &synthDefDir);
  

int main(int argc, char* argv[])
{
  std::string soundfile;
  std::string synthDefDir;
  const char* host;
  const char* port;
  
  if(!init(argc, argv, host, port, soundfile, synthDefDir))
  {
    std::cerr << "Usage Sound_Test <host> <port> <soundfile> <scsyndef directory>" << std::endl;
    return 1;
  }

  SCServer * cs = new SCServer("Server", host, port, synthDefDir);
 // cs->dumpOSC(1);
 
  cs->notify(1);
  usleep(100000);
  
  cs->status();
  Sound * sound = new Sound(cs, soundfile, NEW_PAUSED);

  if(!(sound->isValid()))
  {
    std::cerr << "error creating sound. exiting.";
    return 1;
  }
  
  char key;
  std::cout << "Type q and enter to quit." << std::endl;
  while(key != 'q')
  {
	key = getchar();
	if(key == 'l') 
        {
          if(!(sound->isLooping()))
              sound->setLoop(true);
	  else
	      sound->setLoop(false);
        }

        if(key == 'p')
	{
	  if(!(sound->isPlaying()))
	      sound->play();
          else
	      std::cerr << "sound is already playing!" << std::endl;
        }

        if(key == 's')
	{
	  if(sound->isPlaying())
	      sound->stop();
          else
	      std::cerr << "sound is already stopped!" << std::endl;
        }

        if(key == 'x')
	{
	  cs->queryNode(sound->getId());
        }
   }

  sound->stop();
  delete sound; 
  delete cs;

  return 0;
}
  
bool init(int argc, char* argv[], const char* &host, const char* &port,
				 std::string &soundfile, std::string &synthDefDir)
{
  if(argc != 5)
  {
    return false;
  }

  host = argv[1];
  port = argv[2];
  soundfile = argv[3];
  synthDefDir = argv[4]; 
 
  return true;
}
