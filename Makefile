CXX = g++
CXXFLAGS = -std=c++14 -stdlib=libc++ -Wall -MMD -Werror=vla
EXEC = mvp
OBJECTS = subject.o property.o tile.o player.o board.o game.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
