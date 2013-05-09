all: SoundTest SCServerTest BufferTest

SoundTest: SoundTest.cpp 
	gcc -Wall -o SoundTest SoundTest.cpp -lcollider -lstdc++

SCServerTest: SCServerTest.cpp
	gcc -Wall -o SCServerTest SCServerTest.cpp -lcollider -lstdc++

BufferTest: BufferTest.cpp
	gcc -Wall -o BufferTest BufferTest.cpp -lcollider -lstdc++


clean:
	rm SCServerTest SoundTest BufferTest
