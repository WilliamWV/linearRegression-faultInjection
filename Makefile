# C compiler
CC = g++ -g
CC_FLAGS = -fopenmp
SRC = lreg.cpp
INP_GEN_SRC=generateInput.cpp
EXEC = lreg
EXEC_INP_GEN = genInp
INPUT = randInput
REPORT = reportInput
OUTPUT = goldOutput
LASTRUN = lastDataCreated

destDir = /tmp/lreg

all: gen_bin gen_data mv_bin

gen_bin: $(SRC) $(INP_GEN_SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(EXEC)
	$(CC) $(CC_FLAGS) $(INP_GEN_SRC) -o $(EXEC_INP_GEN)
	
gen_data: gen_bin
	./$(EXEC_INP_GEN) $(INPUT) $(REPORT)
	./$(EXEC) $(INPUT) $(OUTPUT)
mv_bin: gen_data
	mkdir -p $(destDir)
	mkdir -p $(LASTRUN)
	cp $(INPUT) $(REPORT) $(OUTPUT) $(LASTRUN)
	mv $(EXEC_INP_GEN) $(EXEC) $(INPUT) $(REPORT) $(OUTPUT) $(destDir)
	@echo "All Done, executables should be in the $(destDir)"

