#!/usr/bin/env Rscript

library(ggplot2)


# Read csv file with plot data
dat1 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\original\\timeWindow.csv",sep=",",row.names=NULL)
dat2 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\duplication\\timeWindow.csv",sep=",",row.names=NULL)
dat3 = read.csv("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\SelDup\\timeWindow.csv",sep=",",row.names=NULL)

datSdc <- data.frame(
	supp=rep(c("Original", "Duplication", "Selective Duplication"), each=4),
	dose=rep(c(25, 50, 75, 100), 3),
	len=c(as.numeric(dat1[1,]), as.numeric(dat2[1,]), as.numeric(dat3[1,]))
)

# Plot data
ggplot(datSdc, aes(x=dose, y=len, group=supp), method = "lm", formula = y ~ poly(x, 10)) +
  ylim(0,100)+
  geom_line(aes(color=supp), size=1) +
  labs(x = "Time window [%]", y = "PVF/AVF rate [%]", color="Benchmark") +
  theme(legend.position="bottom",axis.text.x=element_text(size=14) , axis.text.y=element_text(size=14) , text = element_text(size = 14)) 

# Save plot to file
ggsave("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\timeWindowSDC.pdf")

datDue <- data.frame(
	supp=rep(c("Original", "Duplication", "Selective Duplication"), each=4),
	dose=rep(c(25, 50, 75, 100), 3),
	len=c(as.numeric(dat1[2,]), as.numeric(dat2[2,]), as.numeric(dat3[2,]))
)


# Plot data
ggplot(datDue, aes(x=dose, y=len, group=supp), method = "lm", formula = y ~ poly(x, 10)) +
ylim(0,100)+
geom_line(aes(color=supp),size=1) +
labs(x = "Time window [%]", y = "PVF/AVF rate [%]") +
theme(legend.position="bottom",axis.text.x=element_text(size=14) , axis.text.y=element_text(size=14) , text = element_text(size = 14)) 

# Save plot to file
ggsave("C:\\Users\\ACEW\\Documents\\UFRGS\\lreg\\timeWindowDUE.pdf")

