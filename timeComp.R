#!/usr/bin/env Rscript

library(ggplot2)


dat <-data.frame(
	dose = c("Original", "Duplication", "Selective Duplication"),
	len = c(2.677, 5.324, 3.125)
)

ggplot(data=dat, aes(x=dose, y=len)) + geom_bar(stat = 'identity', fill="#000077") +ylab("Time") + xlab("Models")

# Save plot to file
ggsave("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\timeComp.pdf", width = 4, height = 5)
