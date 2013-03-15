VPATH =src:include:include/tny_osc
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
  libtype = dynamiclib
  libsuffix = dylib
endif

ifeq ($(UNAME), Linux)
  libtype = shared
  libsuffix = so
endif

libcolliderpp: Client_Server.o Buffer.o Bus.o Node.o Sound.o
	gcc -$(libtype) -o libcollider++.$(libsuffix) src/Client_Server.o src/Buffer.o src/Bus.o src/Node.o src/Sound.o -I/usr/local/include/boost/ -L/usr/local/lib/ -lboost_system -lboost_thread -lpthread -lstdc++ 
	mkdir build
	mv libcollider++.$(libsuffix) build

Client_Server.o : Client_Server.cpp Client_Server.hpp tnyosc.hpp
	gcc -c -fPIC src/Client_Server.cpp -o src/Client_Server.o -Iinclude/ -Iinclude/tny_osc/ -DEH_DEBUG -DTNYOSC_WITH_BOOST

Buffer.o : Buffer.cpp Buffer.hpp
	gcc -c -fPIC src/Buffer.cpp -o src/Buffer.o -Iinclude/ 
Bus.o : Bus.cpp Bus.hpp
	gcc -c -fPIC src/Bus.cpp -o src/Bus.o -Iinclude/ 
Node.o : Node.cpp Node.hpp
	gcc -c -fPIC src/Node.cpp -o src/Node.o -Iinclude/ 
Sound.o : Sound.cpp Sound.hpp
	gcc -c -fPIC src/Sound.cpp -o src/Sound.o -Iinclude/

clean: 
	rm -rf build

install:
	cp build/libcollider++.$(libsuffix) /usr/lib
	chmod 0755 /usr/lib/libcollider++.$(libsuffix)

uninstall:
	rm /usr/lib/libcollider++.$(libsuffix)
