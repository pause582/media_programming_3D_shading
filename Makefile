# Project: media programming 3D shading
# Since the output image is in BMP format, Windows.h is required.
# Recommend: execute this makefile in wsl and compile with g++.exe in mingw-w64

SRC_DIR   = ./src
INC_DIR   = ./include
OBJ_DIR   = ./obj

CPP      = g++.exe

LIB_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(LIB_SRCS))

INCS     =  -I"$(INC_DIR)"

BIN      = solar cube
CFLAGS   = $(INCS) 
RM       = rm

.PHONY: all clean debug

all: $(BIN)

default: all

$(BIN): %: $(OBJ_DIR) $(LIB_OBJS) $(OBJ_DIR)/%.o
	$(CPP) $(OBJ_DIR)/$*.o $(LIB_OBJS) -o $@ $(CFLAGS)

$(patsubst %, $(OBJ_DIR)/%.o, $(BIN)): $(OBJ_DIR)/%.o: %.cpp
	$(CPP) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CPP) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	mkdir $@

debug: $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN)_debug $(LIBS) $(LDLIBS_D) -g

clean: 
	${RM} $(LIB_OBJS) $(patsubst %,$(OBJ_DIR)/%.o,$(BIN)) $(patsubst %,%.exe,$(BIN))
