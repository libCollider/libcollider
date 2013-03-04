VPATH =src:include:include/tny_osc

libcolliderpp: Client_Server.o Buffer.o Bus.o Node.o
	gcc -shared -o libcollider++.so.1.0.1 src/Client_Server.o src/Buffer.o src/Bus.o src/Node.o -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ 
	mkdir build
	mv libcollider++.so.1.0.1 build
	rm -f src/*.o

Client_Server.o : Client_Server.cpp Client_Server.hpp tnyosc.hpp
	gcc -c -fPIC src/Client_Server.cpp -o src/Client_Server.o -Iinclude/ -Iinclude/tny_osc/ -DEH_DEBUG

Buffer.o : Buffer.cpp Buffer.hpp
	gcc -c -fPIC src/Buffer.cpp -o src/Buffer.o -Iinclude/ -Iinclude/tny_osc/ -DEH_DEBUG

Bus.o : Bus.cpp Bus.hpp
	gcc -c -fPIC src/Bus.cpp -o src/Bus.o -Iinclude/ -Iinclude/tny_osc/ -DEH_DEBUG

Node.o : Node.cpp Node.hpp
	gcc -c -fPIC src/Node.cpp -o src/Node.o -Iinclude/ -Iinclude/tny_osc/ -DEH_DEBUG

clean: 
	rm -rf build

install:
	cp build/libcollider++.so.1.0.1 /usr/lib
	chmod 0755 /usr/lib/libcollider++.so.1.0.1

uninstall:
	rm /usr/lib/libcollider++.so.1.0.1

