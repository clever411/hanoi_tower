EXECUTABLE = main
CFLAGS = -c -Wall -O3 -DDEBUG
LDFLAGS =
LIBS = -lsfml-graphics -lsfml-system -lsfml-window -lpthread





# main
all: $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE) 


rebuild: clean $(EXECUTABLE)

rerun: clean $(EXECUTABLE)
	$(EXECUTABLE)



$(EXECUTABLE): main.o HanoiTower.o
	g++ $(LDFLAGS) -o $(EXECUTABLE) main.o HanoiTower.o $(LIBS)

main.o: main.cpp
	g++ $(CFLAGS) -o main.o main.cpp



HanoiTower.o: HanoiTower.cpp
	g++ $(CFLAGS) -o HanoiTower.o HanoiTower.cpp





# clean
clean:
	-rm *.o $(EXECUTABLE)





# end
