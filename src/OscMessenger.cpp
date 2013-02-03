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

const char* OscMessenger::_getPort()
{
  return _port;
}


const char* OscMessenger::_getHost()
{
  return _host;
}

void OscMessenger::_createSynth(string name, int nodeID, int pauseTime)
{
  try {
   #ifdef EH_DEBUG
   cout << "\nSend: /s_new " << name << " " << nodeID <<" command to server..." << endl;
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
   msg.append(nodeID);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   } //end catch
}

void OscMessenger::_killSynth(int nodeID, int pauseTime)
{
   try {
   #ifdef EH_DEBUG
   cout << "\nSend: /n_free " << nodeID <<" command to server..." << endl;
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
   msg.append(nodeID);

   //send the message 
   socket.send_to(buffer(msg.data(), msg.size()), receiver_endpoint);
   } //end try
   
   catch (std::exception& e) {
    cerr << e.what() << endl;
   }
   
}

void OscMessenger::_killServer(int pauseTime)
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

void OscMessenger::_setPort(const char *port)
{
   _port = port;
}

void OscMessenger::_setHost(const char *host)
{
 
  _host = host;
}



  

