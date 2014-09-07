all: clean quick run

main.o: main.cpp
	@g++ -c main.cpp -Wall

time.o: time.cpp
	@g++ -c time.cpp -Wall
	
sdl_basics.o: sdl_basics.cpp
	@g++ -c sdl_basics.cpp -Wall

editor_mapa.o: editor_mapa.cpp
	@g++ -c editor_mapa.cpp -Wall

vnt.o: vnt.cpp
	@g++ -c vnt.cpp -Wall

run:	
	@./exec > debug.out

clean: 
	@rm -rf *.o *~ exec
	
quick: main.o sdl_basics.o time.o vnt.o editor_mapa.o
	@g++ -g main.o sdl_basics.o time.o vnt.o editor_mapa.o -o exec -lSDL2 -lSDL2_ttf -lSDL2_image
