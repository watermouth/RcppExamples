#include <Rcpp.h>

// [[Rcpp::export]]
RcppExport SEXP fun( SEXP x ) {
  BEGIN_RCPP
  int dx = Rcpp::as<int>(x);
  if( dx > 10 )
    throw std::range_error("too big");
  return Rcpp::wrap( dx * dx);
  END_RCPP
}
