all:
	gcc -g playback.c -o playback -lGL -lGLU -lglut -lm
	gcc -g osciliscope.c -o osciliscope -lGL -lGLU -lglut -lm
