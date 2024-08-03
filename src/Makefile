CC = gcc
CXX = g++
CXXFLAGS = -Wall -Werror -g

ifdef OS
	LDFLAGS = -lopengl32 -lpthread --static
else
	LDFLAGS = -lGL -lGLU -lglfw -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor -lasound
endif

INCLUDES = shader.h camera.h SnakePart.h Snake.h Point.h Score.h Shape3D.h constants.h FontRenderer.h gameHandler.h AudioHandler.h

OBJECTS = glad.o stb_image.o process_input.o SnakePart.o Snake.o Point.o Score.o Shape3D.o FontRenderer.o gameHandler.o AudioHandler.o

ifdef OS
game: %: %.o ${OBJECTS}
	mkdir -p build
	$(CXX) $^ ./Libs/glfw3.dll $(CXXFLAGS) $(LDFLAGS) -o build/$@
	cp -r ./assets ./build/
	mkdir -p ./build/assets/audio
	echo "dummy" > ./build/assets/audio/dummy
	cp -r ./images ./build/
	cp -r ./shaders ./build/
	cp ./Libs/glfw3.dll ./build/
else
game: %: %.o ${OBJECTS}
	mkdir -p build
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o build/$@
	cp -r ./assets ./build/
	mkdir -p ./build/assets/audio
	echo "dummy" > ./build/assets/audio/dummy
	cp -r ./images ./build/
	cp -r ./shaders ./build/
endif
	

docs:
	cd ../Docs; doxygen qat.doxygen

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $<

glad.o: ./Libs/glad.c
	$(CC) $(CXXFLAGS) -c $< -o $@

stb_image.o: ./Libs/stb_image.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -rf ../Docs/html ../Docs/latex ./build
