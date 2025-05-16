TARGET = test_list
SRCS = test_list.cpp
CXX = g++-13
OPTIMIZATION = -O3
CXXFLAGS = -Wall -pedantic -std=c++20 -fsanitize=address 

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(OPTIMIZATION) -o $@ $^

clean:
	rm -f $(TARGET)
debug:
	$(CXX) $(CXXFLAGS) -g -o $(TARGET) $(SRCS)
