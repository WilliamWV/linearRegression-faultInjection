#!/usr/bin/env Rscript

library(ggplot2)
args = commandArgs(trailingOnly=TRUE)

if (length(args)<5) {
  stop("At least five argument must be supplied, three input file (CSV file) and two outputfile (PDF name to be created)", call.=FALSE)
}

# Read csv file with plot data
dat1 = read.csv(args[1],sep=",")
dat2 = read.csv(args[2],sep=",")
dat3 = read.csv(args[3],sep=",")

datSdc <- data.frame(
	supp=rep(c("Original", "Duplication", "Selective Duplication"), each=4),
	dose=rep(c(25, 50, 75, 100), 3),
	len=c(dat1[1,], dat2[1,], dat3[1,])
)

datDue <- data.frame(
	supp=rep(c("Original", "Duplication", "Selective Duplication"), each=4),
	dose=rep(c(25, 50, 75, 100), 3),
	len=c(dat1[2,], dat2[2,], dat3[2,])
)

# Plot data
ggplot(datSdc, aes(x=dose, y=len, groups=supp), method = "lm", formula = y ~ poly(x, 10)) +
ylim(0,100)+
geom_line(size=1.1) +
labs(x = "Time window [%]", y = "PVF/AVF rate [%]", color="Benchmark") +
theme(legend.position="bottom",axis.text.x=element_text(size=14) , axis.text.y=element_text(size=14) , text = element_text(size = 14)) 

# Save plot to file
ggsave(args[4])

# Plot data
ggplot(datDue, aes(x=dose, y=len, groups=supp), method = "lm", formula = y ~ poly(x, 10)) +
ylim(0,100)+
geom_line(size=1.1) +
labs(x = "Time window [%]", y = "PVF/AVF rate [%]", color="Benchmark") +
theme(legend.position="bottom",axis.text.x=element_text(size=14) , axis.text.y=element_text(size=14) , text = element_text(size = 14)) 

# Save plot to file
ggsave(args[5])

