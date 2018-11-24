#!/usr/bin/env Rscript

library(ggplot2)
args = commandArgs(trailingOnly=TRUE)

if (length(args)<1) {
  stop("Need one argument to outputfile (PDF name to be created)", call.=FALSE)
}

dat <-data.frame(
	dose = c("Original", "Duplication", "Selective Duplication"),
	len = c(2.677, 5.324, 3.125)
)

ggplot(data=dat, aes(x=dose, y=len)) + geom_bar() +ylab("Percentage") + xlab("Models")

# Save plot to file
ggsave(args[1])
