op:
	@cc -std=c2x -c main.c
	@cc main.o -lvulkan -lglfw -o op
	@glslangValidator -V shader.vert -o vert.spv
	@glslangValidator -V shader.frag -o frag.spv
cl:
	@rm op main.o vert.spv frag.spv
