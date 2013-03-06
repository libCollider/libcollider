VPATH =src:include:include/tny_osc
mac_libsuffix = dylib
mac_libtype = dynamiclib
linux_libsuffix = so
linux_libtype = shared

p = linux

ifeq ($(p), mac)
  libtype = $(mac_libtype)
  libsuffix = $(mac_libsuffix)
endif

ifeq ($(p), linux)
  libtype = $(linux_libtype)
  libsuffix = $(linux_libsuffix)
endif

libcolliderpp: Client_Server.o Buffer.o Bus.o Node.o
	gcc -$(libtype) -o libcollider++.$(libsuffix) src/Client_Server.o src/Buffer.o src/Bus.o src/Node.o -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ 
	mkdir build
	mv libcollider++.$(libsuffix) build
	rm -f src/*.o


Client_Server.o : Client_Server.cpp Client_Server.hpp tnyosc.hpp
	gcc -c -fPIC src/Client_Server.cpp -o src/Client_Server.o -Iinclude/ -Iinclude/tny_osc/ -DEH_DEBUG -DTNYOSC_WITH_BOOST

Buffer.o : Buffer.cpp Buffer.hpp
	gcc -c -fPIC src/Buffer.cpp -o src/Buffer.o -Iinclude/ 
Bus.o : Bus.cpp Bus.hpp
	gcc -c -fPIC src/Bus.cpp -o src/Bus.o -Iinclude/ 
Node.o : Node.cpp Node.hpp
	gcc -c -fPIC src/Node.cpp -o src/Node.o -Iinclude/ 

clean: 
	rm -rf build

install:
	cp build/libcollider++.$(libsuffix) /usr/lib
	chmod 0755 /usr/lib/libcollider++.$(libsuffix)

uninstall:
	rm /usr/lib/libcollider++.$(libsuffix)
