#include <Rcpp.h>
#include <iostream>
using namespace Rcpp;

// [[Rcpp::export]]
RcppExport SEXP example0(SEXP dfMKT){
  DataFrame mkt = as<DataFrame>(dfMKT);
  NumericVector mktprice = mkt(0);
  return(wrap(mktprice[0]));
}

// [[Rcpp::export]]
RcppExport SEXP example1(SEXP df0){
  DataFrame df = as<DataFrame>(df0);
  // Each columns of DataFrame object must be explicitly casted by using as<T>.
  NumericVector x0 = as<NumericVector>(df(0));
  for(int i=0; i < df.nrows(); i++){
    std::cout << x0[i] << ",";
  }
  return(x0);
}

// [[Rcpp::export]]
RcppExport SEXP example2(SEXP a0, SEXP P0, SEXP num){
  int x_num = Rcpp::as<int>(num);
  double x_a0 = Rcpp::as<double>(a0);
  double x_P0 = Rcpp::as<double>(P0);
  for(int i=0; i < x_num; i++){
    x_a0 += x_P0;
  }
  return(Rcpp::wrap<double>(x_a0));
}

/*** R
df01 <- data.frame(id=1:10, strId=c("alice", "bob", "carry", "david", "emanuel", "frin", "george", "hoo", "iris", "joy"))
df02 <- data.frame(a=c(100,200,300), b=c("edo", "nasu", "hida"), stringsAsFactors=F)

out0 <- example0(df01)
out1 <- example1(df01)

out2 <- example2(1.0, 0.1, 7)
*/


