#include "Client_Server.hpp"
#include <iostream>
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "tnyosc.hpp"


using namespace ColliderPlusPlus;

using boost::asio::io_service;
using boost::asio::ip::udp;
using boost::asio::buffer;
using tnyosc::Message;
using tnyosc::Bundle;
using std::cout;
using std::cerr;
using std::cin;
using std::string;
using std::endl;

Client_Server::Client_Server()
:_nextNode(1000), _name("Default Server")
{
  _setHost("127.0.0.1");
  _setPort("57110");
 
  _dumpOSC(1);
   usleep(7000);
  _initialize("../synthdefs/");
}

Client_Server::Client_Server(const std::string& name, const std::string& synthDefDir)
:_nextNode(1000), _name(name)
{
  _setHost("127.0.0.1");
  _setPort("57110");

  _dumpOSC(1);
   usleep(7000);
  _initialize(synthDefDir);
}

Client_Server::Client_Server(const std::string& name, const char *host, 
				    const char *port, const std::string& synthDefDir)
:_nextNode(1000), _name(name)
{
  _setHost(host);
  _setPort(port);

  _dumpOSC(1);
   usleep(7000);
  _initialize(synthDefDir);
}

Client_Server::~Client_Server()
{

}

std::string Client_Server::_getName()
{
  return _name; 
}

//System commands
void Client_Server::_initialize(const std::string& synthDefDir)
{
  _createDefaultGroup(); 
  if(!_loadSynthDefDirectory(synthDefDir))
  {  
    exit(0);
  }
}


int Client_Server::_nextNodeId()
{
   int firstNodeId = _pushFirstNodeId(_nextNode);
  _nextNode++;
    
  return firstNodeId;
}

int Client_Server::_nextBufferNum()
{
  ++_bufferNum;    
  return (_bufferNum-1);
}

void Client_Server::_dumpOSC(int toggle)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /dumpOSC " << toggle <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/dumpOSC");
   msg.append(toggle);
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void Client_Server::_printCurrentNodeIds()
{
  std::vector<int>::iterator iter = _nodeIDs.begin();
  for(; iter != _nodeIDs.end();iter++)
  {
    std::cout << "Node id: " << *iter << std::endl;
  } 
}

void Client_Server::_queryNodeTree()
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /g_dumpTree 0 0 command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/g_dumpTree");
   msg.append(0);
   msg.append(0);
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
} 

//Currently hangs up, don't know why
void Client_Server::_queryNode(int nodeId)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /n_query " << nodeId << " command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/n_query");
   msg.append(nodeId);
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void Client_Server::_pingScsynth()
{


} 

void Client_Server::_quit()
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /quit command to server..." << endl;
   #endif
    
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/quit");   

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif 
   } //end try 

   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}



//OSC/UDP
void Client_Server::_setPort(const char *port)
{
  _port = port;
}

void Client_Server::_setHost(const char *host)
{
  _host = host;
}

const char* Client_Server::_getPort()
{
  return _port;
}


const char* Client_Server::_getHost()
{
  return _host;
}



//Node Commands
void Client_Server::_createNode(int nodeId, int addAction, int target, int type)
{
   std::string typeTag;
  
   try {
   
   if(type == 2)
     typeTag = "/g_new";
   else
     typeTag = "/s_new";  
   

   #ifdef EH_DEBUG
   cout << "\nSend: " << typeTag << " default " << nodeId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg(typeTag);
   msg.append("default");
   msg.append(nodeId);
   msg.append(addAction);
   msg.append(target);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void Client_Server::_createNode(const std::string& name, int nodeId, 
		     int addAction, int target, int type)
{
   try {
   
   std::string typeTag; 
  
   if(type == 2)
     typeTag = "/g_new";  
   else 
     typeTag = "/s_new";
  
 
   #ifdef EH_DEBUG
   cout << "\nSend: " << typeTag << " " << name << " " << nodeId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg(typeTag);
   msg.append(name);
   msg.append(nodeId);
   msg.append(addAction);
   msg.append(target);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void Client_Server::_createSynth(const std::string& name, int nodeId,
					 int addAction, int target)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /s_new " << name << " " << nodeId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/s_new");
   msg.append(name);
   msg.append(nodeId);
   msg.append(addAction);
   msg.append(target);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void Client_Server::_createSynth(const std::string& name, int nodeId,
			std::map<std::string, float> &args, int addAction, int target)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /s_new " << name << " " << nodeId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/s_new");
   msg.append(name);
   msg.append(nodeId);
   msg.append(addAction);
   msg.append(target);
  
   //Iterate through arguments and append to message
   std::map<std::string,float>::iterator i = args.begin();

   for(; i != args.end(); ++i)
   { 
     msg.append((*i).first);
     msg.append((*i).second);
   }
   
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void Client_Server::_createGroup(int nodeId, int addAction, int target)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /g_new " << nodeId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/g_new");
   msg.append(nodeId);
   msg.append(addAction);
   msg.append(target);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

bool Client_Server::_allocBuffer(int bufNum, int numFrames, int numChans)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /b_alloc " << bufNum<< " " << numFrames << " " 
			<< numChans << " command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/b_alloc");
   msg.append(bufNum);
   msg.append(numFrames);
   msg.append(numChans);
 

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   if(recv_from_scsynth_buf[1] == 'f')
   {
     std::cerr << "Failed to allocate buffer!"<<std::endl;
     return false;
   }

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
   
   return false;
}


bool Client_Server::_freeBuffer(int bufNum)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /b_free " << bufNum << " command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/b_free");
   msg.append(bufNum);
   
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   if(recv_from_scsynth_buf[1] == 'f')
   {
     std::cerr << "Failed to free buffer!"<<std::endl;
     return false;
   }

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }

   return false;
}

void Client_Server::_queryBuffer(int bufNum)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /b_query " << bufNum << " command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/b_query");
   msg.append(bufNum);
   
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}

bool Client_Server::_readSoundIntoBuffer(int bufNum, 
			const std::string& filePath, int startFileFrame, 
				int numFrames)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /b_allocRead " << bufNum <<" "<<filePath<<" "
				<<startFileFrame<<" "<<numFrames<<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/b_allocRead");
   msg.append(bufNum);
   msg.append(filePath);
   msg.append(startFileFrame);
   msg.append(numFrames);
     
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   if(recv_from_scsynth_buf[1] == 'f')
   {
     std::cerr << "Failed to create and load buffer!"<<std::endl;
     return false;
   }

   Message callback("/b_query");
   callback.append(bufNum);
   
   //send the message 
   socket.send_to(buffer(callback.data(), callback.size()), receiver_endpoint);

   len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif
   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
   
   return false;
}

void Client_Server::_runNode(int nodeId, int flag)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /n_run " << nodeId << " " << flag << " command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/n_run");
   msg.append(nodeId);
   msg.append(flag);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}

void Client_Server::_freeNode(int nodeId)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /n_free " << nodeId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/n_free");
   msg.append(nodeId);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}

void Client_Server::_setNodeControls(int nodeId, std::map<std::string, float> &controlVals)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /n_set with args command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/n_set");
   msg.append(nodeId);
   
   //Iterate through arguments and append to message
   std::map<std::string,float>::iterator i = controlVals.begin();

   for(; i != controlVals.end(); ++i)
   { 
     msg.append((*i).first);
     msg.append((*i).second);
   }

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}

/*void Client_Server::_setNodeControlRanges(std::map<string, float []> &controlRanges)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /n_setn with args command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/n_set");
   
   //Iterate through arguments and append to message
   std::map<std::string, float[]>::iterator i = controlVals.begin();

   for(; i != args.end(); ++i)
   { 
     msg.append((*i).first);
     msg.append((*i).second);
   }

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}*/

void Client_Server::_freeAllSynths(int groupId)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /g_freeAll " << groupId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/g_freeAll");
   msg.append(groupId);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}

void Client_Server::_deepFreeAllSynths(int groupId)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /g_deepFree " << groupId <<" command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/g_deepFree");
   msg.append(groupId);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
}

bool Client_Server::_loadSynthDef(const std::string& synthDefName)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /d_load " << synthDefName << " command to server..." << endl;
   #endif
    
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/d_load"); 
   msg.append(synthDefName);  

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   if(recv_from_scsynth_buf[1] == 'f')
   {
     std::cerr << "Failed to load synthdef: "<< synthDefName << "!" << std::endl;
     return false;
   }
 
   return true; 
   } //end try 

   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
  
   return false;
}

bool Client_Server::_loadSynthDefDirectory(const std::string& synthDefDir)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /d_loadDir " << synthDefDir << " command to server..." << endl;
   #endif
    
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/d_loadDir"); 
   msg.append(synthDefDir);  

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 1024> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

   #ifdef EH_DEBUG
   std::cout << "\n";
   cout << "Server reply: ";
   cout.write(recv_from_scsynth_buf.data(), len);
   std::cout << "\n\n";
   #endif

   if(recv_from_scsynth_buf[1] == 'f')
   {
     std::cerr << "Failed to load synthdef directory: "<< synthDefDir << "!" << std::endl;
     return false;
   }
 
   return true; 
   } //end try 

   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
  
   return false;
}



//Private
int Client_Server::_pushFirstNodeId(int nextNode)
{
  _nodeIDs.push_back(nextNode);
  return nextNode;
}

void Client_Server::_createDefaultGroup()
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /g_new 1 0 0 command to server..." << endl;
   #endif
   
   //Udp via Boost
   io_service io_service;
   udp::resolver resolver(io_service);
   udp::resolver::query query(udp::v4(), _getHost(), _getPort());
   udp::endpoint receiver_endpoint = *resolver.resolve(query);
   udp::socket socket(io_service);
   socket.open(udp::v4());
   
   //create a OSC message using tnyosc.hpp
   Message msg("/g_new");
   msg.append(1);
   msg.append(0);
   msg.append(0);
   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}
