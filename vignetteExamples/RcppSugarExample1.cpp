#include <Rcpp.h>

// [[Rcpp::export]]
RcppExport SEXP foo( SEXP xs, SEXP ys){
  Rcpp::NumericVector x(xs) ;
  Rcpp::NumericVector y(ys) ;
  return Rcpp::wrap( ifelse( x < y, x*x, -(y*y) )) ;
}

