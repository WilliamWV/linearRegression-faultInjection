# C compiler
CC = g++ -g
CC_FLAGS = -fopenmp
SRC = lreg.cpp
INP_GEN_SRC=generateInput.cpp
EXEC = lreg
EXEC_INP_GEN = genInp
INPUT = randInput
REPORT = reportInput
DETECTED = /tmp/lreg/detected.log
OUTPUT = goldOutput
LASTRUN = lastDataCreated

destDir = /tmp/lreg

all: gen_bin gen_data mv_bin

gen_bin: $(SRC) $(INP_GEN_SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(EXEC)
	$(CC) $(CC_FLAGS) $(INP_GEN_SRC) -o $(EXEC_INP_GEN)
	
gen_data: gen_bin
	./$(EXEC_INP_GEN) $(INPUT) $(REPORT)
	./$(EXEC) $(INPUT) $(OUTPUT) $(DETECTED)
mv_bin: gen_data
	mkdir -p $(destDir)
	mkdir -p $(LASTRUN)
	cp $(INPUT) $(REPORT) $(OUTPUT) $(LASTRUN)
	mv $(EXEC_INP_GEN) $(EXEC) $(INPUT) $(REPORT) $(OUTPUT) $(destDir)
	@echo "All Done, executables should be in the $(destDir)"

graph: lreg

lreg: process_lreg.py parseUtils.py createErrLimitsTableforPlot.R lineGraph.R 
	./process_lreg.py
	./createErrLimitsTableforPlot.R lreg_logs_parsed.csv Lreg errLimit_lreg.csv
	./lineGraph.R errLimit_lreg.csv errLimit_lreg.pdf

clean:
	rm -f lreg_logs_parsed.csv errLimit_lreg.csv errLimit_lreg.pdf parseUtils.pyc
