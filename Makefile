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

INSTALL_DIR = /usr/lib/
BOOST_INCLUDE_DIR = /usr/local/include/boost/
BOOST_LIB_DIR = /usr/local/lib/

libcolliderpp: Client_Server.o Buffer.o Bus.o Node.o Sound.o
	gcc -$(libtype) -o libcollider++.$(libsuffix) src/Client_Server.o src/Buffer.o src/Bus.o src/Node.o src/Sound.o -L$(BOOST_LIB_DIR) -lboost_system -lboost_thread -lpthread -lstdc++ 
	mkdir -p build
	mv libcollider++.$(libsuffix) build

Client_Server.o : Client_Server.cpp Client_Server.hpp tnyosc.hpp
	gcc -c -fPIC src/Client_Server.cpp -o src/Client_Server.o -I$(BOOST_INCLUDE_DIR) -Iinclude/ -Iinclude/tny_osc/ -DTNYOSC_WITH_BOOST -DEH_DEBUG 

Buffer.o : Buffer.cpp Buffer.hpp
	gcc -c -fPIC src/Buffer.cpp -o src/Buffer.o -Iinclude/ 
Bus.o : Bus.cpp Bus.hpp
	gcc -c -fPIC src/Bus.cpp -o src/Bus.o -Iinclude/ 
Node.o : Node.cpp Node.hpp
	gcc -c -fPIC src/Node.cpp -o src/Node.o -Iinclude/ 
Sound.o : Sound.cpp Sound.hpp
	gcc -c -fPIC src/Sound.cpp -o src/Sound.o -Iinclude/

clean: 
	rm src/*.o
	rm -rf $(wildcard build)

install:
	cp build/libcollider++.$(libsuffix) $(INSTALL_DIR)
	chmod 0755 $(INSTALL_DIR)libcollider++.$(libsuffix)

uninstall:
	rm $(INSTALL_DIR)libcollider++.$(libsuffix)
