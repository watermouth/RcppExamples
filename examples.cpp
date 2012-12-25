#include <Rcpp.h>
#include <iostream>
using namespace Rcpp;

// [[Rcpp::export]]
RcppExport SEXP example0(SEXP dfPM, SEXP dfMKT){
  DataFrame mkt = as<DataFrame>(dfMKT);
  NumericVector mktprice = mkt(1);
  return(wrap(mktprice[0]));
}

// [[Rcpp::export]]
RcppExport SEXP example1(SEXP dfPM, SEXP dfMKT){
  DataFrame mkt = as<DataFrame>(dfMKT);
  DataFrame pm  = as<DataFrame>(dfPM);
  for(int i_mkt=0; i_mkt < mkt.nrows(); i_mkt++){
    std::cout << as<NumericVector>(mkt(0))[i_mkt] << ",";
  }
  NumericVector mktprice = mkt(1);
  return(wrap(mktprice[0]));
}

// [[Rcpp::export]]
RcppExport SEXP analisysPL(SEXP dfTRD, SEXP dfPM, SEXP dfMKT){
  DataFrame trd = as<DataFrame>(dfTRD);
  DataFrame mkt = as<DataFrame>(dfMKT);
  DataFrame pm  = as<DataFrame>(dfPM);
  
  NumericVector time_mkt = mkt["ttime"];
  NumericVector time_trd = trd["ttime"];
  
  int i_trd = 0;
  for(int i_mkt=0; i_mkt < mkt.nrows(); i_mkt++) {
    std::cout << time_mkt[i_mkt] << ":::" << time_trd[i_trd] << "_";
    while(time_mkt[i_mkt] >= time_trd[i_trd]){
      i_trd++;
    }
  }
  NumericVector mktprice = mkt["mktprice"];
  return(wrap(mktprice[0]));
}

