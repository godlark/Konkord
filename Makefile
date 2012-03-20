CXX=g++
CXXFLAGS=-Wall
SOURCE=engine.cpp kurs.cpp main.cpp nakladka.cpp RegisterOfErrors.cpp SingleWord.cpp
OBJ=engine.o kurs.o main.o nakladka.o RegisterOfErrors.o SingleWord.o

%.o : %.cpp
	$(CXX) -ggdb3 -c $^ -o $@

konkord.e: $(OBJ)
	$(CXX) $^ -ggdb3 -lboost_regex-mt -ldoublefann -o $@
