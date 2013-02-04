#include "Client_Server.hpp"
#include <cstdlib>
#include <iostream>

#define DEFAULT_PAUSETIME 1

using namespace std;
using namespace ColliderPlusPlus;

/*Function Prototypes*/
//////////////////////
bool processAndInitArgs(int argc, const char* argv[], Client_Server& cs);
void runDemo(Client_Server& cs);

        
int main(int argc, const char* argv[])
{  
   Client_Server cs("Test Server"); 
   if(!(processAndInitArgs(argc, argv, cs)))
   {
     cout << "Exiting.\n" << endl;
     return (EXIT_FAILURE);
   } 

   cout <<"\nClient Server: " << cs._getName() << " using host: " << cs._getOscMessenger()._getHost() 
          << " and port: " << cs._getOscMessenger()._getPort() << "\n" << endl;

   #ifdef FORK_SCSYNTH  
   
   int forkResult = fork();

   //Error Forking
   if(forkResult < 0)
   {
     cout << "Error forking..." << endl;
     return(EXIT_FAILURE);
   }
   
   //Child Process
   else if(forkResult == 0)
   
   {
     #ifdef EH_DEBUG
     cout << "scsynth fork successful...\n" << endl;
     #endif

     int i = execl("/usr/local/bin/scsynth", "/usr/local/bin/scsynth", "-u", cs._getOscMessenger()._getPort(),"-U",
     		 "../../sc_plugins/plugins/", (char*) 0);
   }
  
   //Parent Process
   else
   {
     runDemo(cs);
   }
   
   #else
     runDemo(cs);
   #endif
      
   return 0;
}

void runDemo(Client_Server& cs)
{
  cout << "Starting OSC message sending in 1 seconds..." << endl;
     sleep(DEFAULT_PAUSETIME);
     //Begin test messages
     cs._getOscMessenger()._createNode("default", 
					cs._nextNodeID(), 3);
     sleep(2);
     cs._getOscMessenger()._createNode("default",
					 cs._nextNodeID(), 3);
     sleep(2);
     cs._getOscMessenger()._freeNode(1, 3);
     sleep(2);
     cs._getOscMessenger()._freeNode(2, 3);
     sleep(2);
     cs._getOscMessenger()._killServer(1);   
     sleep(2);
     cout << "The Demo is over. Exiting." << endl;
}

bool processAndInitArgs(int argc, const char* argv[], Client_Server& cs)
{
  if(argc == 1) 
  // Using Defaults
  {
   // cout <<"\nUsing default host: localhost & port: 57110\n"; 
    return true;
  }
 
  if(argc == 2)
  // User supplied host
  {
   // cout <<"\nUsing host: " << argv[1] <<" & port: 57110\n";
    cs._getOscMessenger()._setHost(argv[1]);
    return true;
  }
 
  if(argc == 3)
  // User supplied host and port
  {
   // cout <<"\nUsing host: " << argv[1] <<" & port: " << argv[2] << endl;
    cs._getOscMessenger()._setHost(argv[1]);
    cs._getOscMessenger()._setPort(argv[2]);
    return true;
  }

  cerr << "\nToo many arguments supplied.\n";
  cerr << "\nUsage: client <host> <port>\n";
  
  return false;
}
