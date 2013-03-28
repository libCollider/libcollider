#include "Client_Server.hpp"
#include <iostream>
#include <unistd.h>
#include <list>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

using namespace ColliderPlusPlus;
using namespace tnyosc;
using std::cout;
using std::cerr;
using std::cin;
using std::string;
using std::endl;

void diep(const char * s)
{
  perror(s);
  exit(1);
}

Client_Server::Client_Server()
:_name("Default Server"), _NodeIDGenerator(1000), _BufferIDGenerator(0)
{
  _async_result = false;
  _setHost("127.0.0.1");
  _setPort("57110");
  _setUpOSCDispatcher();
  _createDefaultGroup();
}

Client_Server::Client_Server(const std::string& name, const char *host, 
				    const char *port, const std::string& synthDefDir)
:_name(name), _NodeIDGenerator(1000), _BufferIDGenerator(0)
{
  _async_result = false;
  _setHost(host);
  _setPort(port);
  _setUpOSCDispatcher();
  _createDefaultGroup();
  _initializeSynthDefs(synthDefDir);
}

Client_Server::~Client_Server()
{

}

std::string Client_Server::_getName()
{
  return _name; 
}

void Client_Server::_initializeSynthDefs(const std::string& synthDefDir)
{
  if(!_loadSynthDefDirectory(synthDefDir))
  {  
    cout << "\nError loading synthdefDirectory. Exiting." << endl;
    exit(0);
  }
}

int Client_Server::_nextNodeId()
{
   int nextNode = _NodeIDGenerator++;
   return nextNode;
}

int Client_Server::_nextBufferNum()
{
   int nextBuffer = _BufferIDGenerator++;
   return nextBuffer;
}

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

void Client_Server::_printCurrentNodeIds()
{
  std::vector<int>::iterator iter = _nodeIDs.begin();
  for(; iter != _nodeIDs.end();iter++)
  {
    cout << "Node id: " << *iter << endl;
  } 
}

void Client_Server::send_msg_no_reply(tnyosc::Message * msg, const char * send_msg)
{
   int sockfd;
   struct sockaddr_in servaddr;
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       diep("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons((unsigned short)strtoul(_getPort(), NULL, 0));
   if (inet_aton(_getHost(), &servaddr.sin_addr) == 0)
   {
       cout << "inet_aton() failed" << endl;
       exit(1);
   }

   #ifdef PRINT_DEBUG
   if(send_msg != NULL)
   cout << send_msg << endl;
   #endif
   if (sendto(sockfd, msg->data(), msg->size(), 0, 
			      (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
       diep("sendto()");
   close(sockfd);
}

void Client_Server::send_msg_with_reply(tnyosc::Message * msg, const char * send_msg)
{
   _async_result = false;
   int sockfd, n;
   struct sockaddr_in servaddr;
   char receive_buffer[1024];
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       diep("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons((unsigned short)strtoul(_getPort(), NULL, 0));
   if (inet_aton(_getHost(), &servaddr.sin_addr) == 0)
   {
       cout << "inet_aton() failed" << endl;
       exit(1);
   }

   #ifdef PRINT_DEBUG
   if(send_msg != NULL)
   cout << send_msg << endl;
   #endif
   if (sendto(sockfd, msg->data(), msg->size(), 0, 
			      (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
       diep("sendto()");

   n = recvfrom(sockfd, receive_buffer, sizeof(receive_buffer), 0, NULL, NULL);

   std::list<CallbackRef> callback_list = 
     _dispatcher.match_methods(receive_buffer, n);

   std::list<CallbackRef>::iterator it = callback_list.begin();
     for (; it != callback_list.end(); ++it) {
       (*it)->method((*it)->address, (*it)->argv, (*it)->user_data);
     } 
   close(sockfd);
}

void Client_Server::send_bundle_no_reply(tnyosc::Bundle * bundle, const char * send_msg)
{
   int sockfd;
   struct sockaddr_in servaddr;
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       diep("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(57110);
   if (inet_aton(_getHost(), &servaddr.sin_addr) == 0)
   {
       cout << "inet_aton() failed" << endl;
       exit(1);
   }

   #ifdef PRINT_DEBUG
   if(send_msg != NULL)
   cout << send_msg << endl;
   #endif
   if (sendto(sockfd, bundle->data(), bundle->size(), 0, 
			      (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
       diep("sendto()");
   close(sockfd);
}

void Client_Server::send_bundle_with_reply(tnyosc::Bundle * bundle, const char * send_msg)
{
   _async_result = false;
   int sockfd, n;
   struct sockaddr_in servaddr;
   char receive_buffer[1024];
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       diep("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(57110);
   if (inet_aton(_getHost(), &servaddr.sin_addr) == 0)
   {
       cout << "inet_aton() failed" << endl;
       exit(1);
   }

   #ifdef PRINT_DEBUG
   if(send_msg != NULL)
   cout << send_msg << endl;
   #endif
   if (sendto(sockfd, bundle->data(), bundle->size(), 0, 
			      (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
       diep("sendto()");

   n = recvfrom(sockfd, receive_buffer, sizeof(receive_buffer), 0, NULL, NULL);

   std::list<CallbackRef> callback_list = 
     _dispatcher.match_methods(receive_buffer, n);

   std::list<CallbackRef>::iterator it = callback_list.begin();
     for (; it != callback_list.end(); ++it) {
       (*it)->method((*it)->address, (*it)->argv, (*it)->user_data);
     } 
   close(sockfd);
}

//Commands
void Client_Server::_dumpOSC(int toggle)
{
   Message * msg = new Message("/dumpOSC");
 //  Message msg("/dumpOSC");
   msg->append(toggle);
 
   #ifdef PRINT_DEBUG
   char send_msg[100]; 
   snprintf(send_msg, 100, "\nsending: /dumpOSC %d command to the server", toggle);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif
 
   delete msg;
}

void Client_Server::_queryNodeTree()
{
   Message * msg = new Message("/g_dumpTree");
   msg->append(0);
   msg->append(0);
   
   #ifdef PRINT_DEBUG
   const char * send_msg = "\nsending: /g_dumpTree 0 0 command to the server";
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
} 

//Currently hangs up, don't know why
void Client_Server::_queryNode(int nodeId)
{
   Message * msg = new Message("/n_query");
   msg->append(nodeId);

   #ifdef PRINT_DEBUG
   const char * send_msg = "\nsending: /n_query command to the server";
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
}

void Client_Server::_status()
{
   Message * msg = new Message("/status");  
 
   #ifdef PRINT_DEBUG
   const char * send_msg = "\nsending: /status command to the server";
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
} 

void Client_Server::_quit()
{
   Message * msg = new Message("/quit");

   #ifdef PRINT_DEBUG
   const char * send_msg = "\nsending: /quit command to the server";
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
}

void Client_Server::_createNode(int nodeId, int addAction, int target, int type)
{
   std::string typeTag;

   if(type == 2)
     typeTag = "/g_new";
   else
     typeTag = "/s_new";  
      
   Message * msg = new Message(typeTag);
   msg->append("default");
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);
   send_msg_no_reply(msg);
   delete msg;
}

void Client_Server::_createNode(const std::string& name, int nodeId, 
		     int addAction, int target, int type)
{
   std::string typeTag; 
  
   if(type == 2)
     typeTag = "/g_new";  
   else 
     typeTag = "/s_new";
  
   Message * msg = new Message(typeTag);
   msg->append(name);
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);
   send_msg_no_reply(msg);
   delete msg;
}

void Client_Server::_createSynth(const std::string& name, int nodeId,
					 	int addAction, int target)
{
   Message * msg = new Message("/s_new");
   msg->append(name);
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);
   send_msg_no_reply(msg);
   delete msg;
}

void Client_Server::_createPausedSynth(const std::string& name, int nodeId,
					 	int addAction, int target)
{   
   Message * msg = new Message("/s_new");
   msg->append(name);
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);

   Message * msg2 = new Message("/n_run");
   msg2->append(nodeId);
   msg2->append(0);

   Bundle * bundle = new Bundle();
   bundle->append(msg);
   bundle->append(msg2);
   send_bundle_no_reply(bundle);
   delete bundle;
   delete msg2;
   delete msg;   
}

void Client_Server::_createSynth(const std::string& name, int nodeId,
			std::map<std::string, float> &args, int addAction, int target)
{
   Message * msg = new Message("/s_new");
   msg->append(name);
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);
  
   std::map<std::string,float>::iterator i = args.begin();

      for(; i != args.end(); ++i)
      { 
        msg->append(i->first);
        msg->append(i->second);
      }
   send_msg_no_reply(msg);
   delete msg;
}

void Client_Server::_createPausedSynth(const std::string& name, int nodeId,
			std::map<std::string, float> &args, int addAction, int target)
{
   Message * msg = new Message("/s_new");
   msg->append(name);
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);
  
   std::map<std::string,float>::iterator i = args.begin();

      for(; i != args.end(); ++i)
      { 
        msg->append(i->first);
        msg->append(i->second);
      }

   Message * msg2 = new Message("/n_run");
   msg2->append(nodeId);
   msg2->append(0);

   Bundle * bundle = new Bundle();
   bundle->append(msg);
   bundle->append(msg2);
   send_bundle_no_reply(bundle);
   delete bundle;
   delete msg2;
   delete msg;
}

void Client_Server::_createGroup(int nodeId, int addAction, int target)
{
   Message * msg = new Message("/g_new");
   msg->append(nodeId);
   msg->append(addAction);
   msg->append(target);
   send_msg_no_reply(msg);
   delete msg;
}

bool Client_Server::_allocBuffer(int bufNum, int numFrames, int numChans)
{
   Message * msg = new Message("/b_alloc");
   msg->append(bufNum);
   msg->append(numFrames);
   msg->append(numChans);
   send_msg_with_reply(msg);

   delete msg;
   return _async_result;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /b_alloc " << bufNum<< " " << numFrames << " " 
			<< numChans << " command to server..." << endl;
   #endif*/ 
}

bool Client_Server::_allocReadBuffer(int bufNum, 
			const std::string& filePath, int startFileFrame, 
				int numFrames)
{
   Message * msg = new Message("/b_allocRead");
   msg->append(bufNum);
   msg->append(filePath);
   msg->append(startFileFrame);
   msg->append(numFrames);
   send_msg_with_reply(msg);

   delete msg;
   return _async_result;   
  /* #ifdef PRINT_DEBUG
   cout << "\nSend: /b_allocRead " << bufNum <<" "<<filePath<<" "
			<<startFileFrame<<" "<<numFrames<<" command to server..." << endl;
   #endif*/
}

bool Client_Server::_freeBuffer(int bufNum)
{
   Message * msg = new Message("/b_free");
   msg->append(bufNum);
   
   #ifdef PRINT_DEBUG
   char * send_msg;
   sprintf(send_msg, "sending: /b_free %d command to the server", bufNum);
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
   return _async_result;
}

void Client_Server::_queryBuffer(int bufNum)
{
   Message * msg = new Message("/b_query");
   msg->append(bufNum);
   send_msg_with_reply(msg);
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /b_query " << bufNum << " command to server..." << endl;
   #endif*/
}

void Client_Server::_runNode(int nodeId, int flag)
{
   Message * msg = new Message("/n_run");
   msg->append(nodeId);
   msg->append(flag);
   send_msg_no_reply(msg);
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /n_run " << nodeId << " " << flag << " command to server..." << endl;
   #endif*/
}

void Client_Server::_freeNode(int nodeId)
{
   Message * msg = new Message ("/n_free");
   msg->append(nodeId);
   send_msg_no_reply(msg);
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /n_free " << nodeId <<" command to server..." << endl;
   #endif*/
}

void Client_Server::_setNodeControls(int nodeId, std::map<std::string, float> &controlVals)
{
   Message * msg = new Message ("/n_set");
   msg->append(nodeId);
   
   std::map<std::string,float>::iterator i = controlVals.begin();

   for(; i != controlVals.end(); ++i)
   { 
     msg->append(i->first);
     msg->append(i->second);
   }

   send_msg_no_reply(msg);
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /n_set with args command to server..." << endl;
   #endif*/
}

/*void Client_Server::_setNodeControlRanges(std::map<string, float []> &controlRanges)
{
  try {
   #ifdef PRINT_DEBUG
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
   Message * msg = new Message ("/g_freeAll");
   msg->append(groupId);
   send_msg_no_reply(msg);
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /g_freeAll " << groupId <<" command to server..." << endl;
   #endif*/
}

void Client_Server::_deepFreeAllSynths(int groupId)
{
   Message * msg = new Message ("/g_deepFree");
   msg->append(groupId);
   send_msg_no_reply(msg);
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /g_deepFree " << groupId <<" command to server..." << endl;
   #endif*/
}

bool Client_Server::_loadSynthDef(const std::string& synthDefName)
{
   Message * msg = new Message ("/d_load"); 
   msg->append(synthDefName);  
   send_msg_with_reply(msg);
   delete msg;
   return _async_result;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /d_load " << synthDefName << " command to server..." << endl;
   #endif*/
}

bool Client_Server::_loadSynthDefDirectory(const std::string& synthDefDir)
{
   Message * msg = new Message ("/d_loadDir"); 
   msg->append(synthDefDir); 
  
   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
        "\nsending: /d_loadDir %s command to the server", synthDefDir.c_str());
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
   return _async_result;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /d_loadDir " << synthDefDir << " command to server..." << endl;
   #endif*/
}

void Client_Server::_createDefaultGroup()
{
   Message * msg = new Message ("/g_new");
   msg->append(1);
   msg->append(0);
   msg->append(0);
   send_msg_no_reply(msg);  
   delete msg;
   /*#ifdef PRINT_DEBUG
   cout << "\nSend: /g_new 1 0 0 command to server..." << endl;
   #endif*/
}

//OSC dispatch
void server_done(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{ 
   #ifdef PRINT_DEBUG
   cout << "\nserver received command: " << argv[0].data.s << endl;
   cout << "server reply: " << address << endl;
   #endif
   bool * async_result = (bool*)user_data;	 
   *async_result = true;
}

void fail(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   #ifdef PRINT_DEBUG
   cout << "\nserver received command: " << argv[0].data.s << endl;
   cout << "server reply: " << address << endl;
   cout << "error: : " << argv[1].data.s << endl;
   #endif
   bool * async_result = (bool*)user_data;	 
   *async_result = false;
}

void status_reply(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   if(argv.size() != 9)
   {
      cerr << "status_reply: something went wrong." << endl;
   }

   else
   {
      cout << "server reply: " << address << endl;
     // cout << "command received: " << argv[0].data.s << endl;
   }
}

void node_info(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{


}

void buffer_info(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   if(argv.size() != 4)
   {
      cerr << "buffer_info: something went wrong." << endl;
   }

   else
   {
      cout << "server reply: " << address << endl;
      cout << "command received: " << argv[0].data.s << endl;
   }
}

void Client_Server::_setUpOSCDispatcher()
{
   _dispatcher.add_method("/done", NULL, &server_done, &_async_result);
   _dispatcher.add_method("/fail", NULL, &fail, &_async_result);
   _dispatcher.add_method("/n_info", NULL, &node_info, NULL);
   _dispatcher.add_method("/status.reply", NULL, &status_reply, NULL);
}
