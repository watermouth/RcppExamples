#include <Rcpp.h>

// [[Rcpp::export]]
RcppExport SEXP someFunction() {
  std::vector<std::map<std::string,int> > v;
  std::map<std::string, int> m1;
  std::map<std::string, int> m2;
  m1["foo"]=1;
  m1["bar"]=2;
  m2["foo"]=1;
  m2["bar"]=2;
  m2["baz"]=3;
  v.push_back( m1 );
  v.push_back( m2 );
  return Rcpp::wrap( v );
}

