CC=gcc
CFLAGS=-g -Wall -std=gnu17 -fsanitize=address -static-libasan -lpthread -lm
SRC=src
OBJ=obj
BIN=bin
LIBS=/usr/local/lib/libnng.a
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/*.c, $(OBJ)/*.o, $(SRCS))
EXE=$(BIN)/tars_beta.app

all: $(EXE) 

$(EXE): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
		$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)


clean:
		$(RM) -r $(BIN)/* $(OBJ)/* *dSYM
