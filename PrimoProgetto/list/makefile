# === Variabili ===
TARGET = test_list
SRCS = test_list.cpp
CXX = g++-13

# Flag comuni
CXXFLAGS = -Wall -pedantic -std=c++20

# Build "normale" (con sanitizzatore, ottimizzazione)
RELEASE_FLAGS = -O3 -fsanitize=address

# Build "debug" (niente ottimizzazione, no sanitizzatore)
DEBUG_FLAGS = -g -O0

# === Target principale ===
all: release

release: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -o $@ $^

# === Build in debug ===
debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $(SRCS)

# === Pulizia ===
clean:
	rm -f $(TARGET) $(TARGET)_debug
