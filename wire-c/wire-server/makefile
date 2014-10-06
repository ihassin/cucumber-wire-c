OBJ_PATH=obj
LIB_PATH=lib
BIN_PATH=bin

LIB_FILES=wire-server.c
LIB_OBJ=wire-server.o
LIB_NAME=wire-server.a

all: lib main

$(LIB_PATH)/$(LIB_NAME): $(LIB_FILES)
	gcc -c $(LIB_FILES) -o $(OBJ_PATH)/wire-server.o

lib: $(LIB_PATH)/$(LIB_NAME)
	ar rvs $(LIB_PATH)/$(LIB_NAME) $(OBJ_PATH)/$(LIB_OBJ)

$(OBJ_PATH)/main.o:
	gcc -c main.c -o $(OBJ_PATH)/main.o

main: lib $(OBJ_PATH)/main.o
	gcc -o $(BIN_PATH)/main.out $(OBJ_PATH)/main.o $(LIB_PATH)/$(LIB_NAME)

clean:
	rm -f $(OBJ_PATH)/*
	rm -f $(LIB_PATH)/*
	rm -f $(BIN_PATH)/*
