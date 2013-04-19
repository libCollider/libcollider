all: Sound_Test SCServer_Test Buffer_Test

Sound_Test: Sound_Test.cpp 
	gcc -Wall -o Sound_Test Sound_Test.cpp -lcollider -lstdc++

SCServer_Test: SCServer_Test.cpp
	gcc -Wall -o SCServer_Test SCServer_Test.cpp -lcollider -lstdc++

Buffer_Test: Buffer_Test.cpp
	gcc -Wall -o Buffer_Test Buffer_Test.cpp -lcollider -lstdc++


clean:
	rm SCServer_Test Sound_Test Buffer_Test
