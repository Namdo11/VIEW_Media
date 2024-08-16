# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Sources and objects
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Executable
TARGET = music_player

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) 	$^ -o $@ -lSDL2 -lSDL2_mixer -lSDL2_image -lpthread -lSDL2_ttf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
