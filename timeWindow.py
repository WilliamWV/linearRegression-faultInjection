#!/usr/bin/env python3
'''
	Script para comparar os logs com o gold
'''
import os
import re
import sys

rootDir = 'logs'
outputLog = 'compareLog.log'
goldOutput = 'lastDataCreated/goldOutput'

maxTime = sys.argv[1]
sdcs = [] # lista com diretórios que tem um arquivo output com sdc
dues = []

for dirName, subdirList, fileList in os.walk(rootDir):
	if re.search("sdcs", dirName):
		for file in fileList:
			if re.search("flipvalue", file):
				sdcs.append(file)
	elif re.search("crashes", dirname):
		for file in fileList:
			if re.search("flipvalue", file):
				dues.append(file)
		
sdcCounters = [0, 0, 0, 0]
sdcCount = 0
for file in sdcs:
	sdcF = open(file)
	matches = re.search("Fault Injection Successful after ([0-9e\+\-\.]+).*s")
	time = matches.group(1)
	window = time // (maxTime / 4)
	if window >= 4: 
		window = 3
	sdcCounters[window]+=1
	sdcCount+=1
dueCounters= [0, 0, 0, 0]
dueCount = 0
for file in dues:
	dueF = open(file)
	matches = re.search("Fault Injection Successful after ([0-9e\+\-\.]+).*s")
	time = matches.group(1)
	window = time // (maxTime / 4)
	if window >= 4: 
		window = 3
	dueCounters[window]+=1
	dueCount+=1
print('25,50,75,100') #percentual que representa cada janela
print(str(100*sdcCounters[0]/sdcCount) + ',' + str(100*sdcCounter[1]/sdcCount)+ ',' + str(100*sdcCounter[2]/sdcCount) + ',' + str(100*sdcCounter[3]/sdcCount))
print(str(100*dueCounters[0]/dueCount) + ',' + str(100*dueCounter[1]/dueCount)+ ',' + str(100*dueCounter[2]/dueCount) + ',' + str(100*dueCounter[3]/dueCount))

