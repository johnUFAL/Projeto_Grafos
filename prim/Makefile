CXX = g++ 
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = prim #nome
SOURCES = prim.cpp #arq fonte

$(TARGET): $(SOURCES) #se mudar compila de novo
		$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
		rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

