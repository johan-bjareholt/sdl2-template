
NAME=SDL_Template
CXX=g++
CPPFLAGS=-g --std=c++11

INCLUDES  = -I./libs -I./include \
			-I/usr/include/SDL2/ \
			-I./libs/simple-logger/
LIBRARIES = -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

MAIN		= main gamecontroller graphics font input image sprite timer states/menu

JOBS=1

MAINCPP		= $(patsubst %,src/%.cpp,$(MAIN))
MAINOBJ		= $(patsubst %,obj/%.o,$(MAIN))
LOGGEROBJ	= obj/logger.o
ALLOBJ		= $(MAINOBJ) $(LOGGEROBJ)

.PHONY: all
all: setup compile compile-deps link

#	Sets up folders for objects and binaries
.PHONY: setup
setup:
	mkdir -p obj/{entities,world,states}

#	Compiles source files
obj/%.o: src/%.cpp $(setup)
	$(CXX) -c $(CPPFLAGS) $(INCLUDES) $(LIBRARIES) -o $@ $<

#	Compiles project source
.PHONY: compile
compile: $(setup) ${MAINOBJ}

#	Compiles dependencies
.PHONY: compile-deps
compile-deps: $(setup)
	cd ./libs/simple-logger/ ; $(MAKE) cpp
	cp ./libs/simple-logger/logger.o ./obj/

#	Links objects to a binary
.PHONY: link
link: $(compile-deps) ${MAINOBJ}
	g++ $(CPPFLAGS) -o3 $(INCLUDES) $(LIBRARIES) $(ALLOBJ) -o $(NAME)

.PHONY: clean
clean:
	rm -rf obj
