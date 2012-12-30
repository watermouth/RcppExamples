#include <Rcpp.h>

// [[Rcpp::export]]
RcppExport SEXP lapply_cpp(SEXP listData, SEXP fun){
  Rcpp::List input(listData);
  Rcpp::Function f(fun);
  Rcpp::List output(input.size());
  std::transform(input.begin(), input.end(), output.begin(), f);
  output.names() = input.names();
  return output;
}



