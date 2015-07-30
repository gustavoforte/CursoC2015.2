SRC=src
INC=inc
OBJ=obj
DIST=dist
EXE=bb_leds.exe
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
GCCARGS=-Wall -lws2_32
