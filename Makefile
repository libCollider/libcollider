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
INCLUDE_DIR = /usr/include/

libcolliderpp: tnyosc-dispatch.o Client_Server.o Buffer.o Bus.o Node.o Sound.o 
	gcc -$(libtype) -o libcollider++.$(libsuffix) src/tnyosc-dispatch.o src/Client_Server.o src/Buffer.o src/Bus.o src/Node.o src/Sound.o -lstdc++ 
	mkdir -p build
	mv libcollider++.$(libsuffix) build

tnyosc-dispatch.o : tnyosc-dispatch.cc tnyosc-dispatch.hpp tnyosc.hpp
	gcc -c -fPIC -o src/tnyosc-dispatch.o src/tnyosc-dispatch.cc -Iinclude/tny_osc/

Client_Server.o : Client_Server.cpp Client_Server.hpp tnyosc-dispatch.o
	gcc -c -fPIC -o src/Client_Server.o src/Client_Server.cpp -Iinclude/ -DPRINT_DEBUG

Buffer.o : Buffer.cpp Buffer.hpp
	gcc -c -fPIC -o src/Buffer.o  src/Buffer.cpp -Iinclude/ -DPRINT_DEBUG
Bus.o : Bus.cpp Bus.hpp
	gcc -c -fPIC -o src/Bus.o  src/Bus.cpp -Iinclude/
Node.o : Node.cpp Node.hpp
	gcc -c -fPIC -o src/Node.o  src/Node.cpp -Iinclude/
Sound.o : Sound.cpp Sound.hpp
	gcc -c -fPIC -o src/Sound.o  src/Sound.cpp -Iinclude/

clean: 
	rm src/*.o
	rm -rf $(wildcard build)

install:
	cp build/libcollider++.$(libsuffix) $(INSTALL_DIR)
	mkdir -p $(INCLUDE_DIR)ColliderPlusPlus
	cp -r include/* $(INCLUDE_DIR)ColliderPlusPlus
	chmod 0755 $(INSTALL_DIR)libcollider++.$(libsuffix)

uninstall:
	rm $(INSTALL_DIR)libcollider++.$(libsuffix)
	rm -r $(INCLUDE_DIR)ColliderPlusPlus
