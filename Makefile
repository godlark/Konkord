CXX=g++-4.6
CXXFLAGS=-Wall
SOURCE=engine.cpp kurs.cpp main.cpp nakladka.cpp RegisterOfErrors.cpp SingleWord.cpp trainingData.cpp
OBJ=engine.o kurs.o main.o nakladka.o RegisterOfErrors.o SingleWord.o trainingData.o

%.o : %.cpp
	$(CXX) -ggdb3 -std=c++0x -c $^ -o $@

konkord.e: $(OBJ)
	$(CXX) $^ -ggdb3 -lboost_regex-mt -std=c++0x -ldoublefann -o $@
