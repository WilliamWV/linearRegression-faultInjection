#!/usr/bin/env Rscript

library(ggplot2)
args = commandArgs(trailingOnly=TRUE)

if (length(args)<1) {
  stop("Need one argument to outputfile (PDF name to be created)", call.=FALSE)
}

# Read csv file with plot data
dat1 = read.csv("original/faultReport/original_summary.csv",sep=";",row.names=NULL)
dat2 = read.csv("duplication/faultReport/duplication_summary.csv",sep=";",row.names=NULL)
dat3 = read.csv("SelDup/faultReport/SelDup_summary.csv",sep=";",row.names=NULL)

faultInj1 = as.numeric(levels(dat1[2,2])[as.numeric(dat1[2,2])] + as.numeric(levels(dat1[3,2])[as.numeric(dat1[3,2])] + as.numeric(levels(dat1[4,2])[as.numeric(dat1[4,2])]

faultInj2 = as.numeric(levels(dat2[2,2])[as.numeric(dat2[2,2])] + as.numeric(levels(dat2[3,2])[as.numeric(dat2[3,2])] + as.numeric(levels(dat2[4,2])[as.numeric(dat2[4,2])]

faultInj3 = as.numeric(levels(dat3[2,2])[as.numeric(dat3[2,2])] + as.numeric(levels(dat3[3,2])[as.numeric(dat3[3,2])] + as.numeric(levels(dat3[4,2])[as.numeric(dat3[4,2])]

dat <-data.frame(
	supp = rep(c("Masked", "SDCs", "Crashes", "Hangs"), each=3),
	dose = rep(c("Original", "Duplication", "Selective Duplication"), 4),
	len = c(100 * as.numeric(levels(dat1[2,2])[as.numeric(dat1[2,2])])/faultInj1, 
		  100 * as.numeric(levels(dat2[2,2])[as.numeric(dat2[2,2])])/faultInj2, 
		  100 * as.numeric(levels(dat3[2,2])[as.numeric(dat3[2,2])])/faultInj3, 
		  100 * as.numeric(levels(dat1[3,2])[as.numeric(dat1[3,2])])/faultInj1, 
		  100 * as.numeric(levels(dat2[3,2])[as.numeric(dat2[3,2])])/faultInj2, 
		  100 * as.numeric(levels(dat3[3,2])[as.numeric(dat3[3,2])])/faultInj3, 
		  100 * as.numeric(levels(dat1[4,2])[as.numeric(dat1[4,2])])/faultInj1, 
		  100 * as.numeric(levels(dat2[4,2])[as.numeric(dat2[4,2])])/faultInj2, 
		  100 * as.numeric(levels(dat3[4,2])[as.numeric(dat3[4,2])])/faultInj3, 
		  100 * as.numeric(levels(dat1[5,2])[as.numeric(dat1[5,2])])/faultInj1, 
		  100 * as.numeric(levels(dat2[5,2])[as.numeric(dat2[5,2])])/faultInj2, 
		  100 * as.numeric(levels(dat3[5,2])[as.numeric(dat3[5,2])])/faultInj3, 
		  )
)

ggplot(data=dat, aes(x=dose, y=len, fill=supp)) + geom_bar(position=position_stack(reverse=TRUE)) +ylab("Percentage") + xlab("Models") + coord_flip()+theme(legend.position="top")

# Save plot to file
ggsave(args[1])
