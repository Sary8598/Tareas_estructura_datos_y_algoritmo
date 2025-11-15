# Makefile para Linux y Windows
CXX_LINUX = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -I.
TARGET_LINUX = consultorio
TARGET_WINDOWS = consultorio.exe
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
	$(CXX_WINDOWS) $(CXXFLAGS) -static -o $(TARGET_WINDOWS) $(SRC)
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

# Compilacion con debug para Linux
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET_LINUX)

# Compilacion con debug para Windows
debug-windows: CXXFLAGS += -g -DDEBUG
debug-windows: $(TARGET_WINDOWS)

# Mostrar ayuda
help:
	@echo "Opciones disponibles:"
	@echo "  make linux     - Compilar para Linux"
	@echo "  make windows   - Compilar para Windows"
	@echo "  make both      - Compilar para ambas plataformas"
	@echo "  make run       - Compilar y ejecutar (Linux)"
	@echo "  make debug     - Compilar con debug (Linux)"
	@echo "  make debug-windows - Compilar con debug (Windows)"
	@echo "  make clean     - Limpiar archivos"
	@echo "  make help      - Mostrar esta ayuda"

.PHONY: all linux windows both clean run debug debug-windows help