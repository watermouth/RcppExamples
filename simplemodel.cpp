#include <Rcpp.h>

// [[Rcpp::export]]
RcppExport SEXP simplemodel(SEXP a0, SEXP P0, SEXP num){
  int x_num = Rcpp::as<int>(num);
  double x_a0 = Rcpp::as<double>(a0);
  double x_P0 = Rcpp::as<double>(P0);
  for(int i=0; i < x_num; i++){
    x_a0 += x_P0;
  }
  return(Rcpp::wrap<double>(x_a0));
}
