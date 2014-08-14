all: clean quick run

main.o: main.cpp
	@g++ -c main.cpp -Wall

time1.o: time1.cpp
	@g++ -c time1.cpp -Wall
	
function.o: function.cpp
	@g++ -c function.cpp -Wall

run:	
	@./exec

clean: 
	@rm -rf *.o
	@rm -f exec
	
quick: main.o time1.o function.o
	@g++ -g main.o time1.o function.o -o exec -lSDL -lSDL_ttf -lSDL_image
