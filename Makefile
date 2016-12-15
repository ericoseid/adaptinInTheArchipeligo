glFlags = -lGL -lGLEW -lglfw

evolution: evolution.o landMass.o maleIndividual.o femaleIndividual.o geometry.o
	g++ -std=c++11 -g -o evolution evolution.o maleIndividual.o femaleIndividual.o landMass.o geometry.o $(glFlags)

evolution.o: evolution.cpp
	g++ -std=c++11 -g -c evolution.cpp $(glFlags)

geomtry.o: geometry.h geometry.cpp
	g++ -std=c++11 -g -c geometry.cpp $(glFlags)

landMass.o: landMass.h landMass.cpp
	g++ -std=c++11 -g -c landMass.cpp $(glFlags)

femaleIndividual.o: femaleIndividual.h femaleIndividual.cpp
	g++ -std=c++11 -g -c femaleIndividual.cpp $(glFlags)

maleIndividual.o: maleIndividual.h maleIndividual.cpp 
	g++ -std=c++11 -g -c maleIndividual.cpp $(glFlags)

clean:
	rm -f evolution *.o
