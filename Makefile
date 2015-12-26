rubiks: rubiks.o display.o shader.o mesh.o stb_image.o texture.o transform.o \
camera.o obj_loader.o cube.o
	g++ -g -Wall -std=c++11 -o rubiks rubiks.o display.o shader.o mesh.o \
stb_image.o texture.o transform.o camera.o obj_loader.o cube.o \
-l SDL2 -l GL -l GLEW 

rubiks.o: rubiks.cc display.h shader.h mesh.h texture.h transform.h camera.h \
block.h cube.h
	g++ -g -Wall -std=c++11 -c rubiks.cc

display.o: display.cc display.h
	g++ -g -Wall -std=c++11 -c display.cc

shader.o: shader.cc shader.h transform.h
	g++ -g -Wall -std=c++11 -c shader.cc

mesh.o: mesh.cc mesh.h obj_loader.h
	g++ -g -Wall -std=c++11 -c mesh.cc

stb_image.o: stb_image.c stb_image.h
	gcc -g -Wall -std=c11 -c stb_image.c

texture.o: texture.cc texture.h stb_image.h
	g++ -g -Wall -std=c++11 -c texture.cc

transform.o: transform.cc transform.h
	g++ -g -Wall -std=c++11 -c transform.cc

camera.o: camera.cc camera.h
	g++ -g -Wall -std=c++11 -c camera.cc

obj_loader.o: obj_loader.cc obj_loader.h
	g++ -g -Wall -std=c++11 -c obj_loader.cc

cube.o: cube.cc cube.h block.h texture.h
	g++ -g -Wall -std=c++11 -c cube.cc

clean:
	rm *.o rubiks
