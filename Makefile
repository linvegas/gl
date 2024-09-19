all: build run

build: main.cpp
	g++ -Wall -Wextra -Iinclude/ -o gl main.cpp glad.c -lglfw

run: ./gl
	./gl
	# For legacy old computers that only run opengl < 3.3
	# MESA_GLSL_VERSION_OVERRIDE=330 MESA_GL_VERSION_OVERRIDE=3.3 ./gl
