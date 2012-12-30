#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
SEXP getProfitLossTriggerCoverTrade(int n, SEXP fun){
  Function fun_cpp(fun);
  return(wrap(fun_cpp(n)));
}
// [[Rcpp::export]]
SEXP hoge(SEXP inputdf, SEXP inputfun){
  // DataFrame df = as<DataFrame>(inputdf);
  Function fun(inputfun);
  Function fun2("identity");
  // as<int>(fun2(wrap(1)));
  // fun2(1);
  // fun2(); // error on execution!
    return(wrap(fun(inputdf)));
}
// [[Rcpp::export]]
SEXP callTest1cpp(int index, SEXP inputdf, SEXP inputfun){
  // O.K. ?
  Function fun(inputfun);
  fun(index,inputdf);
  return(fun(index,inputdf));
}
// [[Rcpp::export]]
SEXP ex10(DataFrame input){
  CharacterVector names = input.names();
  for(int i = 0; i<names.size(); i++){
    cout << "names[" << i << "]=" << names[i] << "\n";
  }
  return(names);
}
// [[Rcpp::export]]
SEXP ex10_1(DataFrame input){
  BEGIN_RCPP
  CharacterVector names = input.names();
  // vector<string> str_names = as<string>(names); // error
  string str_names = as<string>(names); // names must have one element.
  for(int i = 0; i<names.size(); i++){
    cout << "names[" << i << "]=" << names[i] << "\n";
  }
  return(wrap(str_names));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex10_2(DataFrame input){
  BEGIN_RCPP
  List names = input.names();
  for(int i = 0; i<names.size(); i++){
    cout << "names[" << i << "]=" << as<string>(names[i]) << "\n"; }
  return(wrap(names));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex10_3(DataFrame input){
  BEGIN_RCPP
  List names = input.names();
  vector<string> strVec;
  for(int i = 0; i<names.size(); i++){
    string s = as<string>(names[i]);
    strVec.push_back(s);
  }
  return(wrap(strVec));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex11(DataFrame input){
  BEGIN_RCPP
  List names = input.names();
  map<string, int> mapObj;
  for(int i = 0; i<names.size(); i++){
    mapObj.insert(pair<string, int>(as<string>(names[i]),i));
  }
  return(wrap(mapObj));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex11_2(DataFrame input){
  BEGIN_RCPP
  List names = input.names();
  map<string, NumericVector> mapObj;
  for(int i = 0; i<names.size(); i++){
    mapObj.insert(pair<string, NumericVector>(as<string>(names[i]),input(i)));
  }
  return(wrap(mapObj));
  END_RCPP
}
void ex12helper(map<string, NumericVector> mapper, string columnName, int rowIndex, double replace){
  (mapper[columnName])(rowIndex) = replace;
}
// [[Rcpp::export]]
SEXP ex12(DataFrame input, CharacterVector columnName, int rowIndex, double replace){
  BEGIN_RCPP
  List names = input.names();
  map<string, NumericVector> mapObj;
  for(int i = 0; i<names.size(); i++){
    mapObj.insert(pair<string, NumericVector>(as<string>(names[i]),input(i)));
  }
  ex12helper(mapObj, as<string>(columnName), rowIndex, replace);
  return(wrap(mapObj));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex12_2(DataFrame input, CharacterVector columnName, double replace){
  BEGIN_RCPP
  List names = input.names();
  map<string, NumericVector> mapObj;
  for(int i = 0; i<names.size(); i++){
    mapObj.insert(pair<string, NumericVector>(as<string>(names[i]),input(i)));
  }
  // all rows
  for(int i=0; i<input.nrows(); i++){
    ex12helper(mapObj, as<string>(columnName), i, replace);
  }
  return(wrap(mapObj));
  END_RCPP
}
// [[Rcpp::export]]
void ex13helper(List mapper, string columnName, int rowIndex, double replace){
  as<NumericVector>(mapper(columnName))(rowIndex) = replace;
}
// [[Rcpp::export]]
SEXP ex13(DataFrame input, CharacterVector columnName, double replace){
  BEGIN_RCPP
  List names = input.names();
  map<string, NumericVector> mapObj;
  for(int i = 0; i<names.size(); i++){
    mapObj.insert(pair<string, NumericVector>(as<string>(names[i]),input(i)));
  }
  // all rows
  for(int i=0; i<input.nrows(); i++){
    ex13helper(wrap(mapObj), as<string>(columnName), i, replace);
  }
  return(wrap(mapObj));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex13_2(DataFrame input, CharacterVector columnName, double replace){
  BEGIN_RCPP
  List names = input.names();
  List mapObj = as<List>(input);
  // all rows
  for(int i=0; i<input.nrows(); i++){
    ex13helper(mapObj, as<string>(columnName), i, replace);
  }
  return(wrap(mapObj));
  END_RCPP
}
// [[Rcpp::export]]
SEXP ex14(DataFrame input, CharacterVector columnName, double replace){
  BEGIN_RCPP
  typedef List L;
  L names = input.names();
  L mapObj = as<L>(input);
  // all rows
  for(int i=0; i<input.nrows(); i++){
    ex13helper(mapObj, as<string>(columnName), i, replace);
  }
  return(wrap(mapObj));
  END_RCPP
}

/*** R
df1 <- data.frame(a=1)
df2 <- data.frame(a=1,b=2,aba=1.3, efa="tilder")
df3 <- data.frame(a=1:3,b=11:13,aba=c(1.3,1.4,8.2), efa=c("tilder", "hat", "camma"))
df12<- df3
a <- seq(from=1,to=1000000,by=1)
df12_2 <- data.frame(a=a, b=cumsum(a))
df13 <- df12_2
df13_2 <- df12_2
df14 <- df12_2
ex11(df1)
print(head(df12_2))
df12Returned <- data.frame(ex12(df12, "a", 1, replace=100.0))
system.time(df12_2Returned <- data.frame(ex12_2(df12_2, "a", replace=100.0)))
system.time(df13Returned <- data.frame(ex13(df13, "a", replace=100.0)))
system.time(df13_2Returned <- data.frame(ex13(df13_2, "a", replace=100.0)))
system.time(df14Returned <- data.frame(ex14(df14, "a", replace=100.0)))
*/
  
  
  