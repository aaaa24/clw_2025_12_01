CPPFLAGS += -Wall -Wexrta -std=c++11
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)
paint: $(SRC)
	$(CXX) $^ -o $@


clean:
	$(RM) -rf $(OBJ) paint
