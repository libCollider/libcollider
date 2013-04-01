VPATH =src:src/tny_osc:include:include/tny_osc
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

libcolliderpp: Client_Server.o Buffer.o Bus.o Node.o Sound.o
	gcc -$(libtype) -o libcollider++.$(libsuffix) src/Client_Server.o src/Buffer.o src/Bus.o src/Node.o src/Sound.o -lstdc++ 
	mkdir -p build
	mv libcollider++.$(libsuffix) build

Client_Server.o : Client_Server.cpp tnyosc-dispatch.cc Client_Server.hpp tnyosc.hpp tnyosc-dispatch.hpp
	gcc -c -fPIC -o src/Client_Server.o src/cs_tnyosc-dispatch_unity.cpp -Iinclude/ -Iinclude/tny_osc/ -DPRINT_DEBUG 

Buffer.o : Buffer.cpp Buffer.hpp
	gcc -c -fPIC -o src/Buffer.o  src/Buffer.cpp -Iinclude/ -Iinclude/tny_osc/ -DPRINT_DEBUG
Bus.o : Bus.cpp Bus.hpp
	gcc -c -fPIC -o src/Bus.o  src/Bus.cpp -Iinclude/ -Iinclude/tny_osc/
Node.o : Node.cpp Node.hpp
	gcc -c -fPIC -o src/Node.o  src/Node.cpp -Iinclude/ -Iinclude/tny_osc/
Sound.o : Sound.cpp Sound.hpp
	gcc -c -fPIC -o src/Sound.o  src/Sound.cpp -Iinclude/ -Iinclude/tny_osc/

clean: 
	rm src/*.o
	rm -rf $(wildcard build)

install:
	cp build/libcollider++.$(libsuffix) $(INSTALL_DIR)
	chmod 0755 $(INSTALL_DIR)libcollider++.$(libsuffix)

uninstall:
	rm $(INSTALL_DIR)libcollider++.$(libsuffix)
