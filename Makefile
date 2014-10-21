CC = g++
CCFLAGS = -Wall
SOURCES = main.cpp
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
OBJECTS=$(SOURCES:.cpp=.o)
EXEC = exec

all: clean create run

perfect: cls reset clean create run cls cat

create:$(OBJECTS)
	@$(CC) $(CCFLAGS) $(OBJECTS) $(LDFLAGS) -o $(EXEC)
run:
	@./$(EXEC)
reset:
	@reset
cat:
	@cat log.out
cls:
	@clear
clean:
	@rm -f *.o *$(EXEC) *~ *.out *.out.*
massif:
	@valgrind --tool=massif --time-unit=ms ./$(EXEC)
