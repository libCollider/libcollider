all: Buffer_Example Node_Example Bus_Example Grain_Example 

 
Buffer_Example: Buffer_Example.cpp
	gcc -Wall -o Buffer_Example Buffer_Example.cpp -I../include/ -I../include/tny_osc -lcollider++ -lstdc++

Node_Example: Node_Example.cpp 
	gcc -Wall -o Node_Example Node_Example.cpp -I../include/ -I../include/tny_osc -lcollider++ -lstdc++

Bus_Example: Bus_Example.cpp 
	gcc -Wall -o Bus_Example Bus_Example.cpp -I../include/ -I../include/tny_osc -lcollider++ -lstdc++

Grain_Example: Grain_Example.cpp
	gcc -Wall -o Grain_Example Grain_Example.cpp -I../include/ -I../include/tny_osc -lcollider++ -lstdc++

clean:
	rm Node_Example Buffer_Example Bus_Example Grain_Example
