TARGET = test_list
SRCS = test_list.cpp list.cpp
CXX = g++
CXXFLAGS = -Wall -pedantic -O3 -std=c++20 -fsanitize=address 

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
