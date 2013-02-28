all: Buffer_Test Node_Test Bus_Test Grain_Test

Buffer_Test: Buffer_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	gcc -Wall -o Buffer_Test Buffer_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -I../../include/tny_osc/ -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ -DEH_DEBUG 

Node_Test: Node_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	gcc -o Node_Test Node_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -I../../include/tny_osc/ -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ -DEH_DEBUG

Bus_Test: Bus_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	gcc -o Bus_Test Bus_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -I../../include/tny_osc/ -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ -DEH_DEBUG

Grain_Test: Grain_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	gcc -o Grain_Test Grain_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -I../../include/tny_osc/ -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ -DEH_DEBUG

clean:
	rm Node_Test Buffer_Test Bus_Test Grain_Test
