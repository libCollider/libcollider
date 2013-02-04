s.boot;
s.dumpOSC(1);
s.queryAllNodes;

x = Synth("default");
y = Synth("default");

s.sendMsg("/s_new", "default", s.nextNodeID, 0, 1);
s.sendMsg("/g_dumpTree", 0, 0); //the "root_node" group, this is an equivalent call to s.queryAllNodes
s.sendMsg("/g_dumpTree", 1, 0); //the default group, this should normally be the target node for synths, new groups, etc
s.sendMsg("/g_deepFree", 1, 0); //frees everything under the default group, including sub groups

//s.sendMsg("/b_alloc", 1, 100);
//s.sendMsg("/b_query", 1);

