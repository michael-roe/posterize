
all: posterize picker picker2

posterize: posterize.c
	gcc -o posterize posterize.c

picker: picker.c
	gcc -o picker picker.c -lm

picker2: picker2.c
	gcc -o picker2 picker2.c -lm
