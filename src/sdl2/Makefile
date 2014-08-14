all: clean quick run

main.o: main.cpp
	@g++ -c main.cpp -Wall

time1.o: time1.cpp
	@g++ -c time1.cpp -Wall
	
sdl_basics.o: sdl_basics.cpp
	@g++ -c sdl_basics.cpp -Wall

vnt.o: vnt.cpp
	@g++ -c vnt.cpp -Wall
run:	
	@./exec

clean: 
	@rm -rf *.o
	@rm -f exec
	
quick: main.o sdl_basics.o time1.o vnt.o 
	@g++ -g main.o sdl_basics.o time1.o vnt.o -o exec -lSDL2 -lSDL2_ttf -lSDL2_image
