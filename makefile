CC = gcc
CFLAGS = -g -I. -c -lm
LFLAGS = `sdl-config --cflags --libs`
ARCHIVOS = Xander.o


%.out:$(ARCHIVOS)
	$(CC) $^ -o $@ $(LFLAGS)
	rm -r *.o

Xander:
	gcc Xander.c -o Xander.out $(LFLAGS)

clean:
	rm -rf *.o *.out

edit:
	kate *.cpp *.hpp