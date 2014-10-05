UNITY_ROOT=../../../unity-master
C_COMPILER=gcc
TARGET_BASE=main
ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.exe
else
	TARGET_EXTENSION=.out
endif
TARGET = $(TARGET_BASE)$(TARGET_EXTENSION)
SRC_FILES=$(UNITY_ROOT)/src/unity.c ./main.c
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src
SYMBOLS=-DTEST

ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q $(TARGET) 
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET)
endif

all: clean default

default:
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) -o $(TARGET)
	./$(TARGET)

clean:
	$(CLEANUP)

