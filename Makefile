rubiks: rubiks.o display.o shader.o mesh.o stb_image.o texture.o transform.o \
camera.o obj_loader.o block.o cube.o
	g++ -g -Wall -std=c++11 -o rubiks rubiks.o display.o shader.o mesh.o \
stb_image.o texture.o transform.o camera.o obj_loader.o block.o cube.o \
-l SDL2 -l GL -l GLEW 

rubiks.o: rubiks.cc display.h shader.h mesh.h transform.h camera.h cube.h
	g++ -g -Wall -std=c++11 -c rubiks.cc

display.o: display.cc display.h
	g++ -g -Wall -std=c++11 -c display.cc

shader.o: shader.cc shader.h transform.h
	g++ -g -Wall -std=c++11 -c shader.cc

mesh.o: mesh.cc mesh.h extern/obj_loader.h
	g++ -g -Wall -std=c++11 -c mesh.cc

stb_image.o: extern/stb_image.c extern/stb_image.h
	gcc -g -Wall -std=c11 -c extern/stb_image.c

texture.o: texture.cc texture.h extern/stb_image.h
	g++ -g -Wall -std=c++11 -c texture.cc

transform.o: transform.cc transform.h
	g++ -g -Wall -std=c++11 -c transform.cc

camera.o: camera.cc camera.h
	g++ -g -Wall -std=c++11 -c camera.cc

obj_loader.o: extern/obj_loader.cc extern/obj_loader.h
	g++ -g -Wall -std=c++11 -c extern/obj_loader.cc

block.o: block.cc block.h texture.h
	g++ -g -Wall -std=c++11 -c block.cc

cube.o: cube.cc cube.h block.h texture.h shader.h transform.h camera.h mesh.h
	g++ -g -Wall -std=c++11 -c cube.cc

clean:
	rm *.o rubiks
