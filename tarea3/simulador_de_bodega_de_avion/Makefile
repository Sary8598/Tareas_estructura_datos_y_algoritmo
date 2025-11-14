CXX = g++
CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS = -Wall -std=c++11 -I.
CXXFLAGS_WIN = -Wall -std=c++11 -I. -static
TARGET = bodega
TARGET_WIN = bodega.exe
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

windows: $(TARGET_WIN)

$(TARGET_WIN): $(SRC)
	$(CXX_WIN) $(CXXFLAGS_WIN) -o $(TARGET_WIN) $(SRC)

clean:
	rm -f $(TARGET) $(TARGET_WIN)

run: $(TARGET)
	./$(TARGET)