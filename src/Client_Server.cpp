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

void error(const char * s)
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
       error("socket");
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
       error("sendto()");
   close(sockfd);
}

void Client_Server::send_msg_with_reply(tnyosc::Message * msg, const char * send_msg)
{
   _async_result = false;
   int sockfd, n;
   struct sockaddr_in servaddr;
   char receive_buffer[1024];
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       error("socket");
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
       error("sendto()");

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
       error("socket");
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
       error("sendto()");
   close(sockfd);
}

void Client_Server::send_bundle_with_reply(tnyosc::Bundle * bundle, const char * send_msg)
{
   _async_result = false;
   int sockfd, n;
   struct sockaddr_in servaddr;
   char receive_buffer[1024];
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       error("socket");
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
       error("sendto()");

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

  #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: %s default %d %d %d command to the server",
			 typeTag.c_str(), nodeId, addAction, target);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

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

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: %s %s %d %d %d command to the server",
			 typeTag.c_str(), name.c_str(), nodeId, addAction, target);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

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
 
   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /s_new %s %d %d %d command to the server",
			 name.c_str(), nodeId, addAction, target);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif
 
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
 
   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending bundle [ \
	 \n/s_new %s %d %d %d \
         \n/n_run %d \
         \n]", name.c_str(), nodeId, addAction, target, nodeId);
   send_bundle_no_reply(bundle, send_msg);
   #else
   send_bundle_no_reply(bundle);
   #endif
 
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

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /s_new %s %d %d %d + args command to the server", 
				name.c_str(), nodeId, addAction, target); 
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

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
 
   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending bundle [ \
	 \n/s_new %s %d %d %d + args \
         \n/n_run %d \
         \n]", name.c_str(), nodeId, addAction, target, nodeId);
   send_bundle_no_reply(bundle, send_msg);
   #else
   send_bundle_no_reply(bundle);
   #endif

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
   
   #ifdef PRINT_DEBUG
   char send_msg[100]; 
   snprintf(send_msg, 100, 
	"\nsending: /g_new %d %d %d command to the server", nodeId, addAction, target);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
}

bool Client_Server::_allocBuffer(int bufNum, int numFrames, int numChans)
{
   Message * msg = new Message("/b_alloc");
   msg->append(bufNum);
   msg->append(numFrames);
   msg->append(numChans);

   #ifdef PRINT_DEBUG
   char send_msg[100]; 
   snprintf(send_msg, 100, 
	"\nsending: /b_alloc %d %d %d command to the server", bufNum, numFrames, numChans);
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
   return _async_result;
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

   #ifdef PRINT_DEBUG
   char send_msg[200]; 
   snprintf(send_msg, 200, 
	"\nsending: /b_allocRead %d %s %d %d command to the server", 
			bufNum, filePath.c_str(), startFileFrame, numFrames);
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
   return _async_result;   
}

bool Client_Server::_freeBuffer(int bufNum)
{
   Message * msg = new Message("/b_free");
   msg->append(bufNum);
   
   #ifdef PRINT_DEBUG
   char send_msg[200];
   snprintf(send_msg, 200, "\nsending: /b_free %d command to the server", bufNum);
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
 
   #ifdef PRINT_DEBUG
   char send_msg[100]; 
   snprintf(send_msg, 100, 
	"\nsending: /b_query %d command to the server", bufNum);
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif
 
   delete msg;
}

void Client_Server::_runNode(int nodeId, int flag)
{
   Message * msg = new Message("/n_run");
   msg->append(nodeId);
   msg->append(flag);

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /n_run %d %d command to the server", nodeId, flag);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
}

void Client_Server::_freeNode(int nodeId)
{
   Message * msg = new Message ("/n_free");
   msg->append(nodeId);

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /n_free %d command to the server", nodeId);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
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

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /n_set %d + args command to the server", nodeId);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
}

void Client_Server::_freeAllSynths(int groupId)
{
   Message * msg = new Message ("/g_freeAll");
   msg->append(groupId);
 
   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /g_freeAll %d command to the server", groupId);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
}

void Client_Server::_deepFreeAllSynths(int groupId)
{
   Message * msg = new Message ("/g_deepFree");
   msg->append(groupId);

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /g_deepFree %d command to the server", groupId);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
}

bool Client_Server::_loadSynthDef(const std::string& synthDefName)
{
   Message * msg = new Message ("/d_load"); 
   msg->append(synthDefName); 
 
   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, 
	"\nsending: /d_load %s command to the server", synthDefName.c_str());
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
   return _async_result;
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
}

void Client_Server::_createDefaultGroup()
{
   Message * msg = new Message ("/g_new");
   msg->append(1);
   msg->append(0);
   msg->append(0);
 
   #ifdef PRINT_DEBUG
   const char * send_msg = "\nsending: /g_new 1 0 0 command to the server";
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif  

   delete msg;
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

//finish me
void status_reply(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   
}

//finish me
void node_info(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{

}

//finish me
void buffer_info(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{

}

void Client_Server::_setUpOSCDispatcher()
{
   _dispatcher.add_method("/done", NULL, &server_done, &_async_result);
   _dispatcher.add_method("/fail", NULL, &fail, &_async_result);
   _dispatcher.add_method("/n_info", NULL, &node_info, NULL); //finish me
   _dispatcher.add_method("/status.reply", NULL, &status_reply, NULL); //finish me
   _dispatcher.add_method("/b_info", NULL, &buffer_info, NULL); //finish me
}
