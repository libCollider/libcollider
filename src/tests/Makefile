all: Buffer_Test Node_Test Bus_Test

Buffer_Test: 
	g++ -o Buffer_Test Buffer_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -L/usr/local/include/boost/ -lboost_system #-DEH_DEBUG 

Node_Test:
	g++ -o Node_Test Node_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -L/usr/local/include/boost/ -lboost_system #-DEH_DEBUG

Bus_Test:
	g++ -o Bus_Test Bus_Test.cpp ../Buffer.cpp ../Client_Server.cpp ../Bus.cpp ../Node.cpp -I../../include/ -L/usr/local/include/boost/ -lboost_system #-DEH_DEBUG

clean:
	rm Node_Test Buffer_Test Bus_Test
