#include <Rcpp.h>
#include <iostream>
using namespace Rcpp;

int updatePosition(NumericVector bcl_pm,
                   NumericVector scl_pm,
                   NumericVector bcn_pm,
                   NumericVector scn_pm,
                   NumericVector time_mkt,
                   NumericVector time_trd,
                   IntegerVector bs_trd,
                   NumericVector lots_trd,
                   int i_mkt,
                   int i_trd,
                   int numTrd,
                   double bclPrev,
                   double sclPrev) {
  std::cout << "i_mkt=" << i_mkt << ", i_trd=" << i_trd << "\n";
  // update position: cumulative sum
  bcl_pm[i_mkt] += bclPrev;
  scl_pm[i_mkt] += sclPrev;
  while(time_mkt[i_mkt] >= time_trd[i_trd] && (i_trd) < numTrd){
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
    (i_trd)++;
  }
  return(i_trd);
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
    // update position: cumulative sum
    i_trd = updatePosition(bcl_pm,
                           scl_pm, bcn_pm, scn_pm,
                           time_mkt,
                           time_trd,
                           bs_trd,
                           lots_trd,
                           i_mkt,
                           i_trd,
                           numTrd,
                           bcl_pm[i_mkt-1],
                           scl_pm[i_mkt-1]
    );
    // pl analysis
    
  }
  NumericVector mktprice = mkt["mktprice"];
  return(wrap(mktprice[0]));
}
