#include <Rcpp.h>
using namespace Rcpp;
// [[Rcpp::export]]
RcppExport SEXP rnormcpp(int n, double sd){
  Environment stats("package:stats");
  Function rnorm = stats["rnorm"];
  return rnorm(n, Named("sd", sd));
}

// [[Rcpp::export]]
RcppExport SEXP rnormcpp2(int n, double sd){
  Language call("rnorm", n, Named("sd",sd));
  return call.eval();
}

// [[Rcpp::export]]
RcppExport SEXP rnormcpp3(int n, double sd){
  RNGScope scope;
  return rnorm(n, 0, sd);
}
