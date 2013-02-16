#include "ColliderPlusPlus.hpp"
#include <unistd.h>
#include <iostream>

using namespace ColliderPlusPlus;

int main()
{
  Client_Server cs("Server");
  Synth s(cs, "default", cs._nextNodeId());
  Buffer b(cs._nextBufferNum());

 // b._alloc(cs, b._getSampRate()*4, 2);
 // std::cout << "bufNum: " << b._getBufNum() << std::endl;
 // b._query(cs); 
 // b._free(cs);
  
  int count = 0;
  while(count < 100)
  {
    b._alloc(cs, b._getSampRate()*4, 2);
 
    b._free(cs);
    ++count;
    usleep(10000);
  }

  s._free(cs);
  cs._quit();

  return 0;
}
