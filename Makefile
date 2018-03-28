CXX = g++-5
CXXFLAGS = -std=c++14  -lX11 -Werror=vla
EXEC = a4q5
OBJECTS = cell.o grid.o textdisplay.o main.o graphicsdisplay.o  window.o
#DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	#${CXX} ${CXXFLAGS} ${OBJECTS} ${ONO} -o ${EXEC}
	g++-5 -std=c++14 *.o -o a4q5 -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
