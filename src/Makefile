CC = gcc
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lGL -lGLU -lglfw -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor

INCLUDES = shader.h texture.h camera.h SnakePart.h Snake.h Point.h Score.h Shape3D.h constants.h FontRenderer.h

game: %: %.o glad.o stb_image.o process_input.o SnakePart.o Snake.o Point.o Score.o Shape3D.o FontRenderer.o
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $<

glad.o: ./Libs/glad.c
	$(CC) $(CXXFLAGS) -c $< -o $@

stb_image.o: ./Libs/stb_image.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f game *.o
