all: Buffer_Test Node_Test Bus_Test

Buffer_Test: Buffer_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	g++ -o Buffer_Test Buffer_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -L/usr/local/include/boost/ -lboost_system #-DEH_DEBUG 

Node_Test: Node_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	g++ -o Node_Test Node_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -L/usr/local/include/boost/ -lboost_system #-DEH_DEBUG

Bus_Test: Bus_Test.cpp ../Buffer.cpp ../Bus.cpp ../Client_Server.cpp ../Node.cpp
	g++ -o Bus_Test Bus_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -L/usr/local/include/boost/ -lboost_system #-DEH_DEBUG

clean:
	rm Node_Test Buffer_Test Bus_Test
