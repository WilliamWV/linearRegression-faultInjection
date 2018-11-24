#!/usr/bin/env Rscript

library(ggplot2)
args = commandArgs(trailingOnly=TRUE)

if (length(args)<4) {
  stop("At least four argument must be supplied, three input file (CSV file) and one outputfile (PDF name to be created)", call.=FALSE)
}

# Read csv file with plot data
dat1 = read.csv(args[1],sep=",")
dat2 = read.csv(args[2],sep=",")
dat3 = read.csv(args[3],sep=",")

dat <- data.frame(
	supp=rep(c("Original", "Duplication", "Selective Duplication"), each=15),
	dose=rep(c(0, 0.1, 0.2, 0.3, 0.4, 0.5, 1, 2, 3, 4, 5, 8, 10, 12, 15), 3),
	len=rep(c(dat1$percentage, dat2$percentage, dat3$percentage))
)

# Plot data
ggplot(dat, aes(x=dose, y=len, groups=supp), method = "lm", formula = y ~ poly(x, 10)) +
ylim(0,100)+
geom_line(size=1.1) +
labs(x = "Tolerated Relative Error [%]", y = "PVF/AVF rate [%]", color="Benchmark") +
theme(legend.position="bottom",axis.text.x=element_text(size=14) , axis.text.y=element_text(size=14) , text = element_text(size = 14)) 

# Save plot to file
ggsave(args[4])
