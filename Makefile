CXX		  := g++
CC		  := gcc
COMMON_FLAGS := -ggdb -Wall -Wextra 
C_FLAGS   := $(COMMON_FLAGS) 
CXX_FLAGS := $(COMMON_FLAGS) -std=c++17

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
RUST_LIB:= target/release
#DEPS	:= board.hpp card.hpp common_ffi.h c_server_binding.h c_server_ffi.hpp deck.hpp game.hpp move.hpp player.hpp russian-bank.hpp server_client.hpp texture_generator.hpp colour.hpp
OBJS 	:= board.o card.o deck.o game.o move.o player.o russian-bank.o server_client.o texture_generator.o c_server_ffi.o c_server_binding.o common_ffi.o

LINK_CXX_LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= Garibaldka
LINK_C_LIBRARIES   := -lserver_client -lpthread -ldl

all: build_rust_lib $(BIN)/$(EXECUTABLE)

run: clean_run all
	clear
	./$(BIN)/$(EXECUTABLE)

%.o: $(SRC)/%.cpp colour.hpp 
	$(CXX) -c $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

c_server_ffi.o: $(SRC)/c_server_ffi.c $(INCLUDE)/c_server_ffi.h
	$(CC) -c $(C_FLAGS) -I$(INCLUDE) $< -o $@ 

common_ffi.o: $(SRC)/common_ffi.c $(INCLUDE)/common_ffi.h
	$(CC) -c $(C_FLAGS) -I$(INCLUDE) $< -o $@ 

c_server_binding.o : c_server_binding
	echo The C library for Rust callbacks is built

$(BIN)/$(EXECUTABLE): $(OBJS) 
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) -L$(RUST_LIB) $^ -o $@ $(LINK_CXX_LIBRARIES) $(LINK_C_LIBRARIES)

c_server_binding: $(SRC)/c_server_binding.c $(INCLUDE)/c_server_binding.h $(SRC) common_ffi.o
	$(CC) -c $(C_FLAGS) -I$(INCLUDE) $< -o $@.o
	ar rcs $(LIB)/lib$@.a $@.o common_ffi.o

build_rust_lib: c_server_binding
	cargo build --release
	cbindgen --lang C  src/server_client.rs > include/rust_server_binding.h

clean_run:
	-echo folder_keeper > bin/folder_keeper

clean: clean_run
	-cargo clean
	-rm $(BIN)/*
	-rm *.o
	-rm $(LIB)/*.a
	
