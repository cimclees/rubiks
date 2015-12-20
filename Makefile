sandbox: sandbox.o display.o shader.o mesh.o
	g++ -g -Wall -std=c++11 -o sandbox sandbox.o display.o shader.o mesh.o \
-l SDL2 -l GL -l GLEW 

sandbox.o: sandbox.cc display.h shader.h
	g++ -g -Wall -std=c++11 -c sandbox.cc

display.o: display.cc display.h
	g++ -g -Wall -std=c++11 -c display.cc

shader.o: shader.cc shader.h
	g++ -g -Wall -std=c++11 -c shader.cc

mesh.o: mesh.cc mesh.h
	g++ -g -Wall -std=c++11 -c mesh.cc
