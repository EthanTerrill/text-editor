


all: main terminal
	gcc main.o terminal.o -o main
main:
	gcc main.c -c


terminal:
	gcc -c terminal.c 
text_editor:
	gcc -c text_editor.c


clean:
	rm -rf *.o *.out main
