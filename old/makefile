CC = gcc
CFLAGS = -g -I. -c -lm
LFLAGS = `sdl-config --cflags --libs`
ARCHIVOS = xander.o


%.out:$(ARCHIVOS)
	$(CC) $^ -o $@ $(LFLAGS)
	rm -r *.o

Xander:
	g++ xander.cpp -o xander.out $(LFLAGS)

clean:
	rm -rf *.o *.out

edit:
	kate *.cpp *.hpp &


# http://www.losersjuegos.com.ar/referencia/articulos/instalar_sdl
# http://www.linuxfromscratch.org/blfs/view/6.0/multimedia/sdl.html
# ./autogen.sh LDFLAGS="-L$(psp-config --pspsdk-path)/lib -lc -lpspuser