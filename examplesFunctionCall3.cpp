#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP ex201(CharacterVector x){
  return(x);
}

// [[Rcpp::export]]
SEXP ex202(CharacterVector x){ // error!
  BEGIN_RCPP
  vector<string> y;
  for(int i=0; i<x.size(); i++){
    y.push_back(as<string>(x[i]));
  }
  return(wrap(y));
  END_RCPP
}

// [[Rcpp::export]]
SEXP ex203(List x){ // 
  BEGIN_RCPP
  vector<string> y;
  for(int i=0; i<x.size(); i++){
    y.push_back(as<string>(x[i]));
  }
  return(wrap(y));
  END_RCPP
}

// [[Rcpp::export]]
SEXP ex204(){ // 
  BEGIN_RCPP
  List y = List::create("hoge","piyo");
  return(y);
  END_RCPP
}

// [[Rcpp::export]]
SEXP ex205(){ // 
  BEGIN_RCPP
  CharacterVector y = CharacterVector::create("hoge","piyo");
  for(int i=0; i<y.size();i++){
    cout << y(i) << " ";
  }
  cout << "\n";
  return(y);
  END_RCPP
}



/*** R
out201 <- ex201(c("hoge", "piyo"))
#out202 <- ex202(c("hoge", "piyo")) // error
out203 <- ex203(c("hoge", "piyo"))
out204 <- ex204()
out205 <- ex205()

*/
