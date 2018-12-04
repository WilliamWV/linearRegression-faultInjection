#!/usr/bin/env Rscript

library(ggplot2)
args = commandArgs(trailingOnly=TRUE)

# Read csv file with plot data
dat1 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\original\\faultReport\\original_summary.csv",sep=";",row.names=NULL)
dat2 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\duplication\\faultReport\\duplication_summary.csv",sep=";",row.names=NULL)
dat3 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\SelDup\\faultReport\\SelDup_summary.csv",sep=";",row.names=NULL)

faultInj1 = as.numeric(levels(dat1[2,2])[as.numeric(dat1[2,2])]) + as.numeric(levels(dat1[3,2])[as.numeric(dat1[3,2])]) + as.numeric(levels(dat1[4,2])[as.numeric(dat1[4,2])])

faultInj2 = as.numeric(levels(dat2[2,2])[as.numeric(dat2[2,2])]) + as.numeric(levels(dat2[3,2])[as.numeric(dat2[3,2])]) + as.numeric(levels(dat2[4,2])[as.numeric(dat2[4,2])])

faultInj3 = as.numeric(levels(dat3[2,2])[as.numeric(dat3[2,2])]) + as.numeric(levels(dat3[3,2])[as.numeric(dat3[3,2])]) + as.numeric(levels(dat3[4,2])[as.numeric(dat3[4,2])])


crash1=floor(100 * as.numeric(levels(dat1[4,2])[as.numeric(dat1[4,2])])/faultInj1)
crash2=floor(100 * as.numeric(levels(dat2[4,2])[as.numeric(dat2[4,2])])/faultInj2)
crash3=floor(100 * as.numeric(levels(dat3[4,2])[as.numeric(dat3[4,2])])/faultInj3)

hangs1=floor(100 * as.numeric(levels(dat1[5,2])[as.numeric(dat1[5,2])])/faultInj1) 
hangs2=floor(100 * as.numeric(levels(dat2[5,2])[as.numeric(dat2[5,2])])/faultInj2) 
hangs3=floor(100 * as.numeric(levels(dat3[5,2])[as.numeric(dat3[5,2])])/faultInj3)

sdcs1=floor(100 * as.numeric(levels(dat1[3,2])[as.numeric(dat1[3,2])])/faultInj1) 
sdcs2=floor(100 * as.numeric(levels(dat2[3,2])[as.numeric(dat2[3,2])])/faultInj2) 
sdcs3=floor(100 * as.numeric(levels(dat3[3,2])[as.numeric(dat3[3,2])])/faultInj3)

masked1=100 - sdcs1 - hangs1 - crash1
masked2=100 - sdcs2 - hangs2 - crash2
masked3=100 - sdcs3 - hangs3 - crash3
  

dat <-data.frame(
	supp = rep(c("Masked", "SDCs", "Crashes", "Hangs"), each=3),
	dose = rep(c("Original", "Duplication", "Selective Duplication"), 4),
	len = c(masked1, masked2, masked3, sdcs1, sdcs2, sdcs3, crash1, crash2, crash3,hangs1, hangs2, hangs3)
)

ggplot(data=dat, aes(x=dose, y=len, fill=supp)) + geom_bar(stat = 'identity', position="stack")+coord_flip() +labs(title = "Results of Fault Injection\n", x = "Models", y = "Percentage", fill = "Result: ") + coord_flip()+theme(legend.position="top")

# Save plot to file
ggsave("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\faultResults.pdf", width = 6, height = 2.5)
