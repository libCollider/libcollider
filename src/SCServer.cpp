#include "SCServer.hpp"
#include "Buffer.hpp"
#include <iostream>
#include <unistd.h>
#include <list>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

using namespace sc;
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

SCServer::SCServer()
:name("Default Server"), NodeIDGenerator(1000), BufferIDGenerator(0), async_result(false)
{
   setHost("127.0.0.1");
   setPort("57110");
   setUpOSCDispatcher();
   createDefaultGroup();
}

SCServer::SCServer(const std::string& n, const char *host, 
				    const char *port, const std::string& synthDefDir)
:name(n), NodeIDGenerator(1000), BufferIDGenerator(0), async_result(false)
{
   setHost(host);
   setPort(port);
   setUpOSCDispatcher();
   createDefaultGroup();
   initializeSynthDefs(synthDefDir);
}

SCServer::~SCServer()
{
  
}

void SCServer::initializeSynthDefs(const std::string& synthDefDir)
{
  if(!loadSynthDefDirectory(synthDefDir))
  {  
    cout << "\nError loading synthdefDirectory. Exiting." << endl;
    exit(0);
  }
}

int SCServer::nextNodeId()
{
   int nextNode = NodeIDGenerator++;
   return nextNode;
}

int SCServer::nextBufferNum()
{
   int nextBuffer = BufferIDGenerator++;
   return nextBuffer;
}

void SCServer::setPort(const char *p)
{
  port = p;
}

void SCServer::setHost(const char *h)
{
  host = h;
}

const char* SCServer::getPort()
{
  return port;
}


const char* SCServer::getHost()
{
  return host;
}

void SCServer::addBuffer(void * buffer)
{ 
   buffers[((Buffer*)buffer)->getBufNum()] = buffer;
}

void SCServer::printCurrentNodeIds()
{
  std::vector<int>::iterator iter = nodeIDs.begin();
  for(; iter != nodeIDs.end();iter++)
  {
    cout << "Node id: " << *iter << endl;
  } 
}

void SCServer::send_msg_no_reply(tnyosc::Message * msg, const char * send_msg)
{
   int sockfd;
   struct sockaddr_in servaddr;
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       error("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons((unsigned short)strtoul(getPort(), NULL, 0));
   if (inet_aton(getHost(), &servaddr.sin_addr) == 0)
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

void SCServer::send_msg_with_reply(tnyosc::Message * msg, const char * send_msg)
{
   async_result = false;
   int sockfd, n;
   struct sockaddr_in servaddr;
   char receive_buffer[1024];
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       error("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons((unsigned short)strtoul(getPort(), NULL, 0));
   if (inet_aton(getHost(), &servaddr.sin_addr) == 0)
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
     dispatcher.match_methods(receive_buffer, n);

   std::list<CallbackRef>::iterator it = callback_list.begin();
     for (; it != callback_list.end(); ++it) {
       (*it)->method((*it)->address, (*it)->argv, (*it)->user_data);
     } 
   close(sockfd);
}

void SCServer::send_bundle_no_reply(tnyosc::Bundle * bundle, const char * send_msg)
{
   int sockfd;
   struct sockaddr_in servaddr;
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       error("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(57110);
   if (inet_aton(getHost(), &servaddr.sin_addr) == 0)
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

void SCServer::send_bundle_with_reply(tnyosc::Bundle * bundle, const char * send_msg)
{
   async_result = false;
   int sockfd, n;
   struct sockaddr_in servaddr;
   char receive_buffer[1024];
   
   if ( (sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
       error("socket");
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(57110);
   if (inet_aton(getHost(), &servaddr.sin_addr) == 0)
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
     dispatcher.match_methods(receive_buffer, n);

   std::list<CallbackRef>::iterator it = callback_list.begin();
     for (; it != callback_list.end(); ++it) {
       (*it)->method((*it)->address, (*it)->argv, (*it)->user_data);
     } 
   close(sockfd);
}

//Commands
void SCServer::dumpOSC(int toggle)
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

void SCServer::queryNodeTree()
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

void SCServer::queryNode(int nodeId)
{
   Message * msg = new Message("/n_query");
   msg->append(nodeId);

   #ifdef PRINT_DEBUG
   char send_msg[100];
   snprintf(send_msg, 100, "\nsending: /n_query %d command to the server", nodeId);
   send_msg_with_reply(msg, send_msg);
   #else
   send_msg_with_reply(msg);
   #endif

   delete msg;
}

void SCServer::status()
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

void SCServer::quit()
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

void SCServer::createNode(int nodeId, int addAction, int target, int type)
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

void SCServer::createNode(const std::string& name, int nodeId, 
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

void SCServer::createSynth(const std::string& name, int nodeId,
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

void SCServer::createPausedSynth(const std::string& name, int nodeId,
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

void SCServer::createSynth(const std::string& name, int nodeId,
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

void SCServer::createPausedSynth(const std::string& name, int nodeId,
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

void SCServer::createGroup(int nodeId, int addAction, int target)
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

bool SCServer::allocBuffer(int bufNum, int numFrames, int numChans)
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
   return async_result;
}

bool SCServer::allocReadBuffer(int bufNum, 
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
   return async_result;   
}

bool SCServer::freeBuffer(int bufNum)
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
   return async_result;
}

void SCServer::freeBuffer_no_reply(int bufNum)
{
   Message * msg = new Message("/b_free");
   msg->append(bufNum);
   
   #ifdef PRINT_DEBUG
   char send_msg[200];
   snprintf(send_msg, 200, "\nsending: /b_free %d command to the server", bufNum);
   send_msg_no_reply(msg, send_msg);
   #else
   send_msg_no_reply(msg);
   #endif

   delete msg;
}


void SCServer::queryBuffer(int bufNum)
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

void SCServer::runNode(int nodeId, int flag)
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

void SCServer::freeNode(int nodeId)
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

void SCServer::setNodeControls(int nodeId, std::map<std::string, float> &controlVals)
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

void SCServer::freeAllSynths(int groupId)
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

void SCServer::deepFreeAllSynths(int groupId)
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

bool SCServer::loadSynthDef(const std::string& synthDefName)
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
   return async_result;
}

bool SCServer::loadSynthDefDirectory(const std::string& synthDefDir)
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
   return async_result;
}

void SCServer::createDefaultGroup()
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

void status_reply(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   cout << "\nstatus.reply: " << endl;
   // argv[0].data.i UNUSED!!
   cout << "# of ugens: " << argv[1].data.i << endl; 
   cout << "# of synths: " << argv[2].data.i << endl;
   cout << "# of groups: " << argv[3].data.i << endl;
   cout << "# of loaded scsyndefs: " << argv[4].data.i << endl;
   cout << "dsp CPU usage: " << argv[5].data.f << endl;
   cout << "dsp CPU peak percent: " <<  argv[6].data.f << endl;
   cout << "nominal sample rate: " << argv[7].data.d << endl;
   cout << "actual sample rate: " << argv[8].data.d << endl;
}

//finish me
void node_info(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   cout << "/node_info reply test" << endl;
}

void buffer_info(const std::string& address, 
		const std::vector<tnyosc::Argument>& argv, void* user_data)
{
   std::map<int, void*> * buffers = (std::map<int, void*> *) user_data;     
   ((Buffer*)((*buffers)[argv[0].data.i]))->setNumFrames(argv[1].data.i);
   ((Buffer*)((*buffers)[argv[0].data.i]))->setNumChans(argv[2].data.i);
   ((Buffer*)((*buffers)[argv[0].data.i]))->setSampRate(argv[3].data.f);
}

void SCServer::setUpOSCDispatcher()
{
   dispatcher.add_method("/done", NULL, &server_done, &async_result);
   dispatcher.add_method("/fail", NULL, &fail, &async_result);
   dispatcher.add_method("/n_info", NULL, &node_info, NULL); //finish me
   dispatcher.add_method("/status.reply", NULL, &status_reply, NULL); 
   dispatcher.add_method("/b_info", NULL, &buffer_info, &buffers);
}
