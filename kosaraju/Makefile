CXX = g++ 
CXXFLAGS = -std=c++20 -Wall -O2
TARGET = kosaraju
SOURCES = kosaraju.cpp 

$(TARGET): $(SOURCES) 
		$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
		rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
