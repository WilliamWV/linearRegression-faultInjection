# C compiler
CC = g++ -g
CC_FLAGS = -fopenmp
SRC = lreg.cpp
EXEC = lreg

all: gen_bin gen_data mv_bin

gen_bin: $(SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(EXEC)
	
gen_data: gen_bin
	# nothing now
mv_bin: gen_data
	# nothing now
