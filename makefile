exec :  displayable.o frame.o interface.o solid.o pivot.o sliding.o robot.o main.o
	g++ -o exec displayable.o frame.o interface.o solid.o pivot.o sliding.o robot.o main.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

displayable.o : displayable.cpp displayable.hpp
	g++ -c displayable.cpp

frame.o : frame.cpp frame.hpp
	g++ -c frame.cpp

interface.o : interface.cpp interface.hpp
	g++ -c interface.cpp

solid.o : solid.cpp solid.hpp
	g++ -c solid.cpp

pivot.o : pivot.cpp pivot.hpp
	g++ -c pivot.cpp 

sliding.o : sliding.cpp sliding.hpp
	g++ -c sliding.cpp

robot.o : robot.cpp robot.hpp
	g++ -c robot.cpp

main.o : main.cpp main.hpp 
	g++ -c main.cpp

clean:
	rm -rf *.o
	rm -f exec


#OBJS = affichable.o repere.o interface.o solid.o pivot.o glissiere.o robot.o main.o


#exec:$(OBJS)
#	g++ -g -o $@ $^ -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2

#%.o: %.cpp
#	g++ -g -c $<



