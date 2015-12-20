sandbox: sandbox.o display.o shader.o mesh.o stb_image.o texture.o
	g++ -g -Wall -std=c++11 -o sandbox sandbox.o display.o shader.o mesh.o \
stb_image.o texture.o -l SDL2 -l GL -l GLEW 

sandbox.o: sandbox.cc display.h shader.h mesh.h texture.h
	g++ -g -Wall -std=c++11 -c sandbox.cc

display.o: display.cc display.h
	g++ -g -Wall -std=c++11 -c display.cc

shader.o: shader.cc shader.h
	g++ -g -Wall -std=c++11 -c shader.cc

mesh.o: mesh.cc mesh.h
	g++ -g -Wall -std=c++11 -c mesh.cc

stb_image.o: stb_image.c stb_image.h
	gcc -g -Wall -std=c11 -c stb_image.c

texture.o: texture.cc texture.h stb_image.h
	g++ -g -Wall -std=c++11 -c texture.cc
