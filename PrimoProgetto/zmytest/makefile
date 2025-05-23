# === Variabili principali ===
TARGET = test
SRCS = test.cpp #inserire nel cpp un main() che chiama le funzioni di test
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

CXX = g++-13

# Flag comuni
CXXFLAGS = -Wall -pedantic -std=c++20 -MMD -MP

# Flag per build ottimizzata con AddressSanitizer
RELEASE_FLAGS = -O3 -fsanitize=address

# Flag per build di debug
DEBUG_FLAGS = -g -O0

# === Target di default ===
all: release

# === Build ottimizzata ===
release: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -o $@ $^

# === Build di debug ===
debug: $(SRCS)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $^

# === Pulizia dei file generati ===
clean:
	rm -f $(TARGET) $(TARGET)_debug $(OBJS) $(DEPS)

# === Inclusione automatica dei file di dipendenza ===
-include $(DEPS)
