all: clean quick run

quick: main.o editor_mapa.o sdl_basics.o
	@g++ main.o editor_mapa.o sdl_basics.o -o exec -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

main.o: main.cpp
	@g++ -c main.cpp -Wall

editor_mapa.o: editor_mapa.cpp
	@g++ -c editor_mapa.cpp -Wall

sdl_basics.o: sdl_basics.cpp
	@g++ -c sdl_basics.cpp -Wall
	
run: 
	@./exec

clean:
	@rm -rf *.o *exec
