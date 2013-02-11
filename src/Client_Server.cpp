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
}

Client_Server::Client_Server(const std::string& name)
:_nextNode(1000), _name(name)
{
  _setHost("127.0.0.1");
  _setPort("57110");
}

Client_Server::Client_Server(const std::string& name, const char *host, const char *port)
:_nextNode(1000), _name(name)
{
  _setHost(host);
  _setPort(port);
}

Client_Server::~Client_Server()
{

}

std::string Client_Server::_getName()
{
  return _name; 
}



//System commands
void Client_Server::_boot()
{
  _createDefaultGroup(); 
}

int Client_Server::_nextNodeId()
{
   int firstNodeId = _pushFirstNodeId(_nextNode);
  _nextNode++;
    
  return firstNodeId;
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

bool Client_Server::_pingScsynth()
{
  return false;
} 


void Client_Server::_quitServer()
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
   boost::array<char, 256> recv_from_scsynth_buf;
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
bool Client_Server::_createNode(int nodeId)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /s_new default " << nodeId <<" command to server..." << endl;
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
   msg.append("default");
   msg.append(nodeId);
   msg.append(0);
   msg.append(1);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
   return false;

}

bool Client_Server::_createNode(const std::string& name, int nodeId)
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
   msg.append(0);
   msg.append(1);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
   return false;

}

bool Client_Server::_createSynth(const std::string& name, int nodeId)
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
   msg.append(0);
   msg.append(1);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
   return false;
}

/*bool Client_Server::_createGroup(std::string& name, int nodeId)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /g_new " << name << " " << nodeId <<" command to server..." << endl;
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
   msg.append(name);
   msg.append(nodeId);
   msg.append(0);
   msg.append(1);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
   return false;
}*/

bool Client_Server::_runNode(int nodeId, int flag)
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

   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
   return false;
}

bool Client_Server::_freeNode(int nodeId)
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
   return true;
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
   return false;
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
   boost::array<char, 256> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

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

bool Client_Server::_loadSynthDefDirectory(const std::string& dirName)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /d_loadDir " << dirName << " command to server..." << endl;
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
   msg.append(dirName);  

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);

   //receive return message from server -- will this work since scsynth's repsonse is asynchronous?
   boost::array<char, 256> recv_from_scsynth_buf;
   udp::endpoint sender_endpoint;
   size_t len = socket.receive_from(buffer(recv_from_scsynth_buf), sender_endpoint);

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
   cout << "\nSend: /g_new 0 0 command to server..." << endl;
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
