CXX = clang++
C = clang
CXX_VERSION = c++20

NAME = bess

INCLUDE = -Iinclude/ -I../external/glad/include -I../external/imgui -I../external/imgui/backends

SRC_DIR = src

TARGET_DIR = ../out/

SRC_FILES = $(wildcard $(SRC_DIR)/*/*.cpp)
SRC_FILES += $(wildcard $(SRC_DIR)/*/*/*.cpp)
SRC_FILES += $(wildcard $(SRC_DIR)/*.cpp)

EXT_SRC_FILES = ../external/glad/src/glad.c

EXT_SRC_FILES_CPP = $(wildcard ../external/imgui/*.cpp)
EXT_SRC_FILES_CPP += $(wildcard ../external/imgui/*/*.cpp)

TARGET = $(TARGET_DIR)$(NAME)

OBJECTS = $(patsubst %.cpp, %.o,$(SRC_FILES))
OBJECTS += $(patsubst %.c, %.o,$(EXT_SRC_FILES))
OBJECTS += $(patsubst %.cpp, %.o,$(EXT_SRC_FILES_CPP))

LIBS = -lglfw -lGL 

DEPS = $(OBJECTS)

$(NAME): $(TARGET)

$(TARGET): $(DEPS) | $(TARGET_DIR)
	$(CXX) -o $@ -std=$(CXX_VERSION) $(OBJECTS) $(LIB_INCLUDE_DIRS) $(LIBS)

%.o: %.cpp
	$(CXX) -std=$(CXX_VERSION) $(INCLUDE) -c $< -o $@

%.o: %.c
	$(C) $(INCLUDE) -c $< -o $@

$(TARGET_DIR)%a:
	make -C ../$(subst .a,,$(@F))

run: $(NAME)
	$(TARGET)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

