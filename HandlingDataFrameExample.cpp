#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
RcppExport SEXP ex1(DataFrame input){
  return(wrap(input)); // without wrap may be O.K.
}


// [[Rcpp::export]]
RcppExport SEXP ex2(DataFrame input, int i){
//  NumericVector x1 = input(_,1); // compile error
  i--;
  NumericVector x1_1 = input(i);
  NumericVector x1_2 = input[i];
//  return(NumericVector::create(x1_1, x1_2)); // error
  return(DataFrame::create(Named("A")=x1_1, Named("B") = x1_2));
}

// [[Rcpp::export]]
RcppExport SEXP ex3(DataFrame input, int i){
  i--;
  BEGIN_RCPP
  if( i < 0 )
    throw std::range_error("too small");
  List names = input.names();
  if( i >= names.size())
    throw std::range_error("too big");
  NumericVector x = input[i];
  NumericVector::iterator it = x.begin();
  for(;it != x.end(); ++it){
    *it = *it - 1;
  }
//  return(*it); cannot convert 'double' to "SEXPREC*" in return
  return(input);
  END_RCPP
}

// [[Rcpp::export]]
RcppExport SEXP ex4(DataFrame input, int i){
  i--;
  BEGIN_RCPP
  if( i < 0 )
    throw std::range_error("too small");
  List names = input.names();
  if( i >= names.size())
    throw std::range_error("too big");
  END_RCPP
  NumericVector x = input[i];
  NumericVector::iterator it = x.begin();
  for(;it != x.end(); ++it){
    *it = *it - 1;
  }
//  return(*it); cannot convert 'double' to "SEXPREC*" in return
  return(input);
}

/*** R
df1 <- data.frame(a=1,b=3,name="light")
out1 <- ex1(df1)
print(all(df1 == out1))

df2 <- data.frame(name="Feynman", age=53, sex="M", height=183.2)
out2 <- ex2(df2,1)

tdate <- as.Date("2012-12-20")
# tdate <- seq(from=tdate, to = tdate + 20,by=1)
tdate <- rep(tdate,10)
ttime <- seq(from=0,to=90,along.with=tdate)
buysell <- c(0,1,0,1,1,1,0,1,0,0)
lots <- c(seq(from=1000,to=5000,by=1000), 1000, 1000, 10000, 8000, 2000)
price <- seq(from=78,to=87,along.with=tdate)
df3 <- data.frame(tdate,ttime,buysell,lots,price)
out3 <- ex3(df3,0)


*/

