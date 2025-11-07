CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = research_manager
SOURCES = main.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) research.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run