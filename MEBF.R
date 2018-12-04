#!/usr/bin/env Rscript

library(ggplot2)


# Read csv file with plot data
#Para saber da criticidade
dat1 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\original\\errLimit_lreg.csv",sep=",")
dat2 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\duplication\\errLimit_lreg.csv",sep=",")
dat3 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\SelDup\\errLimit_lreg.csv",sep=",")

# Read csv file with plot data
dat4 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\original\\faultReport\\original_summary.csv",sep=";",row.names=NULL)
dat5 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\duplication\\faultReport\\duplication_summary.csv",sep=";",row.names=NULL)
dat6 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\SelDup\\faultReport\\SelDup_summary.csv",sep=";",row.names=NULL)

faultInj1 = as.numeric(levels(dat4[2,2])[as.numeric(dat4[2,2])]) + as.numeric(levels(dat4[3,2])[as.numeric(dat4[3,2])]) + as.numeric(levels(dat4[4,2])[as.numeric(dat4[4,2])])

faultInj2 = as.numeric(levels(dat5[2,2])[as.numeric(dat5[2,2])]) + as.numeric(levels(dat5[3,2])[as.numeric(dat5[3,2])]) + as.numeric(levels(dat5[4,2])[as.numeric(dat5[4,2])])

faultInj3 = as.numeric(levels(dat6[2,2])[as.numeric(dat6[2,2])]) + as.numeric(levels(dat6[3,2])[as.numeric(dat6[3,2])]) + as.numeric(levels(dat6[4,2])[as.numeric(dat6[4,2])])

originalSDC_MEBF = 1/((as.numeric(levels(dat4[3,2])[as.numeric(dat4[3,2])])/faultInj1) * 2.677)
duplicationSDC_MEBF = 1/((as.numeric(levels(dat5[3,2])[as.numeric(dat5[3,2])])/faultInj2) * 5.324)
selDupSDC_MEBF = 1/((as.numeric(levels(dat6[3,2])[as.numeric(dat6[3,2])])/faultInj3) * 3.125)

originalCritical_MEBF = 1/((dat1$percentage[13]/100.0) * (as.numeric(levels(dat4[3,2])[as.numeric(dat4[3,2])])/faultInj1) * 2.677)
duplicationCritical_MEBF = 1/((dat2$percentage[13]/100.0) * (as.numeric(levels(dat4[3,2])[as.numeric(dat4[3,2])])/faultInj1) * 5.324)
selDupCritical_MEBF = 1/((dat3$percentage[13]/100.0) * (as.numeric(levels(dat4[3,2])[as.numeric(dat4[3,2])])/faultInj1) * 3.125)


dat <-data.frame(
	supp = rep(c("SDC", "SDC critical"), each=3),
	dose = rep(c("Original", "Duplication", "Selective Duplication"), 2),
	len = c(originalSDC_MEBF, duplicationSDC_MEBF, selDupSDC_MEBF, 
			originalCritical_MEBF, duplicationCritical_MEBF, selDupCritical_MEBF
		  )
)

ggplot(data=dat, aes(x=dose, y=len, fill=supp)) + geom_bar(stat="identity", position=position_dodge()) +ylab("MEBF") + xlab("Models")

# Save plot to file
ggsave("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\MEBF.pdf")

#quantidade de dados corretos até dado errado

#quantidade de dados corretos ao todos / sdcs
#sdcs/exec*quantidade de falhas injetadas

#error rate = sdcs/quantidade de falhas
#MEBF = 1/error rate * exec

