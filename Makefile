all: build run
legacy: build run-legacy

build: main.cpp
	g++ -Wall -Wextra -Iinclude/ -o gl main.cpp glad.c -lglfw

run: ./gl
	./gl

# For old legacy computers that only run opengl < 3.3
run-legacy: ./gl
	MESA_GLSL_VERSION_OVERRIDE=330 MESA_GL_VERSION_OVERRIDE=3.3 ./gl
