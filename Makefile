CXX=g++
CXXFLAGS=-Wall
SOURCE_ENGINE=kurs.cpp RegisterOfErrors.cpp
OBJ_ENGINE=kurs.o RegisterOfErrors.o

konkord: $(OBJ_ENGINE) nakladka.o
	$(CXX) $^ -lboost_regex-mt -o $@

nakladka.o: nakladka.cpp
	$(CXX) -c $^ -o $@

$(OBJ_ENGINE): $(SOURCE_ENGINE)
	$(CXX) -c $^
