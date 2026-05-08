CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET   = build/HotelKeycard
SRCS     = src/Hotel.cpp src/Keycard.cpp src/KeycardManager.cpp src/Utils.cpp
OBJS     = $(SRCS:src/%.cpp=build/%.o)

.PHONY: all clean run setup

all: setup $(TARGET)

setup:
	@mkdir -p build data

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Build successful → $(TARGET)"

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build/ data/keycards.txt
	@echo "✓ Cleaned build artifacts."
