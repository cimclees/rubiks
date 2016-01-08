rubiks: build/rubiks.o build/display.o build/shader.o build/mesh.o \
build/stb_image.o build/texture.o build/transform.o build/camera.o \
build/obj_loader.o build/block.o build/cube.o
	g++ -g -Wall -std=c++11 -o rubiks build/rubiks.o build/display.o \
build/shader.o build/mesh.o build/stb_image.o build/texture.o \
build/transform.o build/camera.o build/obj_loader.o build/block.o build/cube.o \
-l SDL2 -l GL -l GLEW 

build/rubiks.o: src/rubiks.cc include/display.h include/shader.h \
include/mesh.h include/transform.h include/camera.h include/cube.h
	g++ -g -Wall -std=c++11 -c src/rubiks.cc -o build/rubiks.o

build/display.o: src/display.cc include/display.h
	g++ -g -Wall -std=c++11 -c src/display.cc -o build/display.o

build/shader.o: src/shader.cc include/shader.h include/transform.h
	g++ -g -Wall -std=c++11 -c src/shader.cc -o build/shader.o

build/mesh.o: src/mesh.cc include/mesh.h lib/obj_loader.h
	g++ -g -Wall -std=c++11 -c src/mesh.cc -o build/mesh.o

build/stb_image.o: lib/stb_image.c lib/stb_image.h
	gcc -g -Wall -std=c11 -c lib/stb_image.c -o build/stb_image.o

build/texture.o: src/texture.cc include/texture.h lib/stb_image.h
	g++ -g -Wall -std=c++11 -c src/texture.cc -o build/texture.o

build/transform.o: src/transform.cc include/transform.h
	g++ -g -Wall -std=c++11 -c src/transform.cc -o build/transform.o

build/camera.o: src/camera.cc include/camera.h
	g++ -g -Wall -std=c++11 -c src/camera.cc -o build/camera.o

build/obj_loader.o: lib/obj_loader.cc lib/obj_loader.h
	g++ -g -Wall -std=c++11 -c lib/obj_loader.cc -o build/obj_loader.o

build/block.o: src/block.cc include/block.h include/texture.h
	g++ -g -Wall -std=c++11 -c src/block.cc -o build/block.o

build/cube.o: src/cube.cc include/cube.h include/block.h include/texture.h \
include/shader.h include/transform.h include/camera.h include/mesh.h
	g++ -g -Wall -std=c++11 -c src/cube.cc -o build/cube.o

clean:
	rm -f build/* rubiks
