CC = gcc
CXX = g++
CXXFLAGS = -Wall -Werror -g
LDFLAGS = -lGL -lGLU -lglfw -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor

INCLUDES = shader.h camera.h SnakePart.h Snake.h Point.h Score.h Shape3D.h constants.h FontRenderer.h gameHandler.h

OBJECTS = glad.o stb_image.o process_input.o SnakePart.o Snake.o Point.o Score.o Shape3D.o FontRenderer.o gameHandler.o

game: %: %.o ${OBJECTS}
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

docs:
	cd ../Docs; doxygen qat.doxygen

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $<

glad.o: ./Libs/glad.c
	$(CC) $(CXXFLAGS) -c $< -o $@

stb_image.o: ./Libs/stb_image.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f game *.o
