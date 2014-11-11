CC = g++
CCFLAGS = -Wall
SOURCES = main.cpp Controller/Game.cpp Model/Item.cpp Model/Player.cpp Utility/ResourceManager.cpp Utility/Timer.cpp Utility/Tools.cpp View/SDLmodule.cpp
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
OBJECTS=$(SOURCES:.cpp=.o)
EXEC = exec
MACOSX = -L/opt/local/lib

all: clean create run

perfect: cls reset clean create run cls cat

create:$(OBJECTS)
	@$(CC) $(CCFLAGS) $(OBJECTS) $(MACOSX) $(LDFLAGS) -o $(EXEC)
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
