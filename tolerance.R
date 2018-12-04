#!/usr/bin/env Rscript

library(ggplot2)


# Read csv file with plot data
dat1 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\original\\errLimit_lreg.csv",sep=",")
dat2 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\duplication\\errLimit_lreg.csv",sep=",")
dat3 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\SelDup\\errLimit_lreg.csv",sep=",")

dat <- data.frame(
	supp=rep(c("Original", "Duplication", "Selective Duplication"), each=15),
	dose=rep(c(0, 0.1, 0.2, 0.3, 0.4, 0.5, 1, 2, 3, 4, 5, 8, 10, 12, 15), 3),
	len=c(dat1$percentage, dat2$percentage, dat3$percentage)
)

# Plot data
ggplot(dat, aes(x=dose, y=len, group=supp), method = "lm", formula = y ~ poly(x, 10)) +
ylim(0,100)+
geom_line(aes(color=supp),size=1) +
labs(x = "Tolerated Relative Error [%]", y = "PVF/AVF rate [%]", color="Benchmark") +
theme(legend.position="bottom",axis.text.x=element_text(size=14) , axis.text.y=element_text(size=14) , text = element_text(size = 14)) 

# Save plot to file
ggsave("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\tolerance.pdf", width = 8, height = 6)
