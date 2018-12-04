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

maxTime = 3
sdcs = [] # lista com diretórios que tem um arquivo output com sdc
dues = []

for dirName, subdirList, fileList in os.walk(rootDir):
	if re.search("sdcs", dirName):
		for file in fileList:
			if re.search("flipvalue", file):
				sdcs.append(dirName + "\\\\" + file)
	elif re.search("crashes", dirName):
		for file in fileList:
			if re.search("flipvalue", file):
				dues.append(dirName + "\\\\" + file)
		
sdcCounters = [0, 0, 0, 0]
sdcCount = 0
for file in sdcs:
	sdcF = open(file)
	sdcLines = sdcF.readlines()
	for line in sdcLines:
		if(line[:15] == "Fault Injection"):
			tline = line[33:len(line)-2]
			time = float(tline)
			window = int(time // (maxTime / 4))
			if window >= 4: 
				window = 3
			sdcCounters[window]+=1
			sdcCount+=1
dueCounters= [0, 0, 0, 0]
dueCount = 0
for file in dues:
	dueF = open(file)
	dueLines = dueF.readlines()
	for line in dueLines:
		if(line[:15] == "Fault Injection"):
			tline = line[33:len(line)-2]
			time = float(tline)
			window = int(time // (maxTime / 4))
			if window >= 4: 
				window = 3
			dueCounters[window]+=1
			dueCount+=1
print('25,50,75,100') #percentual que representa cada janela
print(str(100*sdcCounters[0]/sdcCount) + ',' + str(100*sdcCounters[1]/sdcCount)+ ',' + str(100*sdcCounters[2]/sdcCount) + ',' + str(100*sdcCounters[3]/sdcCount))
print(str(100*dueCounters[0]/dueCount) + ',' + str(100*dueCounters[1]/dueCount)+ ',' + str(100*dueCounters[2]/dueCount) + ',' + str(100*dueCounters[3]/dueCount))

