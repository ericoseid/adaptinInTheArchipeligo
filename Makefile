glFlags = -lGL -lGLEW -lglfw

evolution: evolution.o maleIndividual.o femaleIndividual.o landMass.o
	g++ -std=c++11 -o evolution evolution.o maleIndividual.o femaleIndividual.o landMass.o $(glFlags)

evolution.o: evolution.cpp
	g++ -std=c++11 -c evolution.cpp $(glFlags)

maleIndividual.o: maleIndividual.h maleIndividual.cpp
	g++ -std=c++11 -c maleIndividual.cpp $(glFlags)

femaleIndividual.o: femaleIndividual.h femaleIndividual.cpp
	g++ -std=c++11 -c femaleIndividual.cpp $(glFlags)

landMass.o: landMass.h landMass.cpp
	g++ -std=c++11 -c landMass.cpp $(glFlags)

clean:
	rm -f evolution *.o
