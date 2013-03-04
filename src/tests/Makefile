all: Buffer_Test Node_Test Bus_Test Grain_Test

Buffer_Test: Buffer_Test.cpp
	gcc -Wall -o Buffer_Test Buffer_Test.cpp -I../../include/ -lcollider++ -lstdc++

Node_Test: Node_Test.cpp 
	gcc -o Node_Test Node_Test.cpp -I../../include/ -lcollider++ -lstdc++

Bus_Test: Bus_Test.cpp 
	gcc -o Bus_Test Bus_Test.cpp -I../../include/ -lcollider++ -lstdc++

Grain_Test: Grain_Test.cpp
	gcc -o Grain_Test Grain_Test.cpp -I../../include/ -lcollider++ -lstdc++

clean:
	rm Node_Test Buffer_Test Bus_Test Grain_Test
