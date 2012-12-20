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

#include <Rcpp.h>
#include <iostream>
using namespace Rcpp;



// [[Rcpp::export]]
RcppExport SEXP analisysPL(SEXP dfTRD, SEXP dfPM, SEXP dfMKT){
  DataFrame trd = as<DataFrame>(dfTRD);
  DataFrame mkt = as<DataFrame>(dfMKT);
  DataFrame pm  = as<DataFrame>(dfPM);
  
  NumericVector time_mkt = mkt["ttime"];
  NumericVector time_trd = trd["ttime"];
  IntegerVector bs_trd   = trd["buysell"];
  NumericVector lots_trd = trd["lots"];
  NumericVector bcl_pm   = pm["bCumLots"];
  NumericVector scl_pm   = pm["sCumLots"];
  NumericVector bcn_pm   = pm["bCustNums"];
  NumericVector scn_pm   = pm["sCustNums"];
  NumericVector pl_pm   = pm["pl"];
  int numTrd = trd.nrows();
  int i_trd = 0;
  for(int i_mkt=0; i_mkt < mkt.nrows(); i_mkt++) {
    std::cout << "i_mkt=" << i_mkt << ", i_trd=" << i_trd << "\n";
    while(time_mkt[i_mkt] >= time_trd[i_trd] && i_trd < numTrd){
      // update position
      switch(bs_trd[i_trd]){
        case 0:
          bcl_pm[i_mkt] += lots_trd[i_trd];
          
        break;
        case 1: as<NumericVector>(pm["sCumLots"])[i_mkt] += lots_trd[i_trd];
        break;
      }
      i_trd++;
    }
    // pl analysis
  }
  NumericVector mktprice = mkt["mktprice"];
  return(wrap(mktprice[0]));
}

// [[Rcpp::export]]
RcppExport SEXP analisysPL(SEXP dfTRD, SEXP dfPM, SEXP dfMKT){
  DataFrame trd = as<DataFrame>(dfTRD);
  DataFrame mkt = as<DataFrame>(dfMKT);
  DataFrame pm  = as<DataFrame>(dfPM);
  
  NumericVector time_mkt = mkt["ttime"];
  NumericVector time_trd = trd["ttime"];
  IntegerVector bs_trd   = trd["buysell"];
  NumericVector lots_trd = trd["lots"];
  NumericVector bcl_pm   = pm["bCumLots"];
  NumericVector scl_pm   = pm["sCumLots"];
  NumericVector bcn_pm   = pm["bCustNums"];
  NumericVector scn_pm   = pm["sCustNums"];
  NumericVector pl_pm   = pm["pl"];
  int numTrd = trd.nrows();
  int i_trd = 0;
  for(int i_mkt=1; i_mkt < mkt.nrows(); i_mkt++) {
    std::cout << "i_mkt=" << i_mkt << ", i_trd=" << i_trd << "\n";
    // update position: cumulative sum
    bcl_pm[i_mkt] += bcl_pm[i_mkt-1];
    scl_pm[i_mkt] += scl_pm[i_mkt-1];
    while(time_mkt[i_mkt] >= time_trd[i_trd] && i_trd < numTrd){
      // update position
      switch(bs_trd[i_trd]){
        case 0:
          bcl_pm[i_mkt] += lots_trd[i_trd];
          bcn_pm[i_mkt] += 1;  
        break;
        case 1:
          scl_pm[i_mkt] += lots_trd[i_trd];
          scn_pm[i_mkt] += 1;
        break;
      }
      i_trd++;
    }
    // pl analysis
    
  }
  NumericVector mktprice = mkt["mktprice"];
  return(wrap(mktprice[0]));
}


