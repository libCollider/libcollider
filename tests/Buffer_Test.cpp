#include "ColliderPlusPlus.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace ColliderPlusPlus;

bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir);
  
void print_info(Buffer &buffer);

int main(int argc, char* argv[])
{
  std::string synthDefDir;
  const char* host;
  const char* port;
  
  if(!init(argc, argv, host, port, synthDefDir))
  {
    std::cerr << "Usage Buffer_Test <host> <port> <scsyndef directory>" << std::endl;
    return 1;
  }
   
  std::cout << "\nRunning Buffer test..." << std::endl;

  Client_Server cs("Server", host, port, synthDefDir);
  cs._dumpOSC(1);
  Buffer b(&cs, cs._nextBufferNum());
  Buffer c(&cs, cs._nextBufferNum());
  Buffer d(&cs, cs._nextBufferNum());
  print_info(b);
  print_info(c);
  print_info(d);
  b._allocRead("/Users/administrator/Music/test_audio/cheesecake.aiff");
  c._allocRead("/Users/administrator/Music/test_audio/bass_clarinet-d3.wav");
  d._allocRead("/Users/administrator/Music/all-8ch.wav");
  print_info(b);
  print_info(c);
  print_info(d);
  
  std::vector<Buffer*> buffers (10); 
  std::vector<Buffer*>::iterator it;
  for(it = buffers.begin(); it != buffers.end() ; it++)
  {
     *it = new Buffer(&cs, cs._nextBufferNum());
     (*it)->_alloc(1024, 2);   
  }
  
  for(it = buffers.begin(); it != buffers.end() ; it++)
  {
     (*it)->_free();
     delete *it;
  }
  
  d._free();
  c._free();
  b._free();

  //cs._quit();   

  return 0;
}
  
bool init(int argc, char* argv[], const char* &host, const char* &port, std::string &synthDefDir)
{
  if(argc != 4)
  {
    return false;
  }

  host = argv[1];
  port = argv[2];
  synthDefDir = argv[3]; 
 
  return true;
}

void print_info(Buffer &buffer)
{
  std::cout << "\nbuffer # " << buffer._getBufNum() << std::endl;
  std::cout << "# of frames: " << buffer._getFrameNum() << std::endl;
  std::cout << "# of channels: " << buffer._getChanNum() << std::endl;
  std::cout << "samplerate: " << buffer._getSampRate() << std::endl;
}
