CXX = g++
CXXFLAGS = -Wall -std=c++11 -I.
TARGET = parqueo

# Lista todos los archivos .cpp
SRC = main.cpp \
      entities/Vehicle.cpp \
      repositories/ParkingRepository.cpp \
      services/ParkingService.cpp \
      controllers/ParkingController.cpp \
      views/ParkingView.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run