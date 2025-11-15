# Makefile para Linux y Windows
CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -I.
TARGET_LINUX = banco
TARGET_WINDOWS = banco.exe
SRC = main.cpp

# Compilacion por defecto (Linux)
all: linux

# Compilar para Linux
linux: $(TARGET_LINUX)

$(TARGET_LINUX): $(SRC)
	@echo "Compilando para Linux..."
	$(CXX_LINUX) $(CXXFLAGS) -o $(TARGET_LINUX) $(SRC)
	@echo "Compilacion exitosa: $(TARGET_LINUX)"

# Compilar para Windows
windows: $(TARGET_WINDOWS)

$(TARGET_WINDOWS): $(SRC)
	@echo "Compilando para Windows..."
	$(CXX_WINDOWS) $(CXXFLAGS) -o $(TARGET_WINDOWS) $(SRC)
	@echo "Compilacion exitosa: $(TARGET_WINDOWS)"

# Compilar para ambas plataformas
both: linux windows
	@echo "Compilacion completada para Linux y Windows"

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos..."
	rm -f $(TARGET_LINUX) $(TARGET_WINDOWS)
	@echo "Limpieza completada"

# Ejecutar version Linux
run: $(TARGET_LINUX)
	@echo "Ejecutando $(TARGET_LINUX)..."
	./$(TARGET_LINUX)
