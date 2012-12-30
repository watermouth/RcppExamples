# for test
tdate <- as.Date("2012-12-20")
# tdate <- seq(from=tdate, to = tdate + 20,by=1)
tdate <- rep(tdate,10)
ttime <- seq(from=0,to=90,along.with=tdate)
buysell <- c(0,1,0,1,1,1,0,1,0,0)
lots <- c(seq(from=1000,to=5000,by=1000), 1000, 1000, 10000, 8000, 2000)
price <- seq(from=78,to=87,along.with=tdate)

df <- data.frame(tdate,ttime,buysell,lots,price)

numRate <- 10
# mid_rate <- rep(80.001,numRate);
mid_rate <- rnorm(n=numRate,mean=80,sd=5)
bid_rate <- mid_rate - 0.001
ask_rate <- mid_rate + 0.001
mktpricedf <- data.frame(ttime=seq(mid_rate), bid_rate, mid_rate, ask_rate)
nrows <- nrow(mktpricedf)

positionManager <- data.frame(ttime=mktpricedf[["ttime"]],
                              bCumLots=vector(mode="numeric",length=nrows),
                              sCumLots=vector(mode="numeric",length=nrows),
                              bCustNums=vector(mode="numeric",length=nrows),
                              sCustNums=vector(mode="numeric",length=nrows),
                              bCumAmts=vector(mode="numeric",length=nrows),
                              sCumAmts=vector(mode="numeric",length=nrows),
                              pl=vector(mode="numeric", length=nrows)
)




