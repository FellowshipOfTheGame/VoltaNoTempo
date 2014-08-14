all: clean quick run

main.o: main.cpp
	@g++ -c main.cpp -Wall


run:	
	@./exec

clean: 
	@rm -rf *.o
	@rm -f exec
	
quick: main.o
	@g++ -g main.o -o exec -lSDL2 -lSDL2_ttf -lSDL2_image -lBox2D

