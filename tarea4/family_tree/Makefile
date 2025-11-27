# Makefile para Windows y Linux
CXX = g++
CXXFLAGS = -Wall -std=c++11 -Iincludes
TARGET = family_tree

# Detectar el sistema operativo
ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe
    RM = del /Q
    MKDIR = mkdir
    SOURCES = src\main.cpp \
              src\entities\Person.cpp \
              src\repositories\FamilyRepository.cpp \
              src\services\FamilyTreeService.cpp \
              src\controllers\FamilyController.cpp \
              src\views\FamilyView.cpp
    OBJ_DIR = obj
    OBJECTS = $(SOURCES:src\%.cpp=$(OBJ_DIR)\%.o)
    CREATE_DIR = if not exist $(subst /,\,$(1)) $(MKDIR) $(subst /,\,$(1))
else
    RM = rm -f
    MKDIR = mkdir -p
    SOURCES = src/main.cpp \
              src/entities/Person.cpp \
              src/repositories/FamilyRepository.cpp \
              src/services/FamilyTreeService.cpp \
              src/controllers/FamilyController.cpp \
              src/views/FamilyView.cpp
    OBJ_DIR = obj
    OBJECTS = $(SOURCES:src/%.cpp=$(OBJ_DIR)/%.o)
    CREATE_DIR = $(MKDIR) $(1)
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regla para Windows
$(OBJ_DIR)\%.o: src\%.cpp
	@$(call CREATE_DIR,$(@D))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para Linux
$(OBJ_DIR)/%.o: src/%.cpp
	@$(call CREATE_DIR,$(@D))
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)
	$(RM) -r $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET)

# Para Windows
ifeq ($(OS),Windows_NT)
run: $(TARGET)
	.\$(TARGET)
endif

.PHONY: all clean run
