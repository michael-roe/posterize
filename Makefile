
all: posterize picker

posterize: posterize.c
	gcc -o posterize posterize.c

picker: picker.c
	gcc -o picker picker.c -lm
