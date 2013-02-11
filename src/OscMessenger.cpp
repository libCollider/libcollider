#include "OscMessenger.hpp"

#include <iostream>
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "tnyosc.hpp"

using std::cout;
using std::cerr;
using std::cin;
using std::string;
using std::endl;
using boost::asio::io_service;
using boost::asio::ip::udp;
using boost::asio::buffer;
using tnyosc::Message;
using tnyosc::Bundle;

using namespace ColliderPlusPlus;

#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_PORT "57110"

OscMessenger::OscMessenger()
{
  _setHost(DEFAULT_HOST);
  _setPort(DEFAULT_PORT);
}

OscMessenger::~OscMessenger()
{

}

void OscMessenger::_boot()
{
  //boot

  _createDefaultGroup();
}

void OscMessenger::_createDefaultGroup()
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

void OscMessenger::_dumpOSC(int toggle)
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

bool OscMessenger::_createNode(int nodeId)
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

bool OscMessenger::_createSynth(const std::string& name, int nodeId)
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

/*bool OscMessenger::_createGroup(const std::string& name, int nodeId)
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

bool OscMessenger::_runNode(int nodeId, int flag)
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


bool OscMessenger::_freeNode(int nodeId)
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

void OscMessenger::_quitServer()
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

void OscMessenger::_queryNodeTree()
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

bool OscMessenger::_loadSynthDef(const std::string& synthDefName)
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

bool OscMessenger::_loadSynthDefDirectory(const std::string& dirName)
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

void OscMessenger::_setPort(const char *port)
{
   _port = port;
}

void OscMessenger::_setHost(const char *host)
{
 
  _host = host;
}

const char* OscMessenger::_getPort()
{
  return _port;
}


const char* OscMessenger::_getHost()
{
  return _host;
}



  

