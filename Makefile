
all: posterize

posterize: posterize.c
	gcc -o posterize posterize.c
