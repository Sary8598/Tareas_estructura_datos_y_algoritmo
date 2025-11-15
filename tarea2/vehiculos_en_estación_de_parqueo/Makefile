CXX = g++
CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS = -Wall -std=c++11 -I.
CXXFLAGS_WIN = -Wall -std=c++11 -I. -static
TARGET = parqueo
TARGET_WIN = parqueo.exe

# Lista todos los archivos .cpp
SRC = main.cpp \
      entities/Vehicle.cpp \
      repositories/ParkingRepository.cpp \
      services/ParkingService.cpp \
      controllers/ParkingController.cpp \
      views/ParkingView.cpp

OBJ = $(SRC:.cpp=.o)
OBJ_WIN = $(SRC:.cpp=.obj)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

windows: $(TARGET_WIN)

$(TARGET_WIN): $(OBJ_WIN)
	$(CXX_WIN) $(CXXFLAGS_WIN) -o $(TARGET_WIN) $(OBJ_WIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.obj: %.cpp
	$(CXX_WIN) $(CXXFLAGS_WIN) -c $< -o $@

clean:
	rm -f $(TARGET) $(TARGET_WIN) $(OBJ) $(OBJ_WIN)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run windows