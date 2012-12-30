#include <Rcpp.h>
#include <iostream>
using namespace Rcpp;

int updatePosition( NumericVector bcl_pm,
                    NumericVector scl_pm,
                    NumericVector bca_pm,
                    NumericVector sca_pm,
                    NumericVector bcn_pm,
                    NumericVector scn_pm,
                    NumericVector time_mkt,
                    NumericVector time_trd,
                    IntegerVector bs_trd,
                    NumericVector lots_trd,
                    NumericVector price_trd,
                    int i_mkt,
                    int i_trd,
                    int numTrd,
                    double bclPrev,
                    double sclPrev,
                    double bcaPrev,
                    double scaPrev ) {
//    std::cout << "i_mkt=" << i_mkt << ", i_trd=" << i_trd << "\n";
    // update position: cumulative sum
    bcl_pm[i_mkt] += bclPrev;
    scl_pm[i_mkt] += sclPrev;
    bca_pm[i_mkt] += bcaPrev;
    sca_pm[i_mkt] += scaPrev;
    while(time_mkt[i_mkt] >= time_trd[i_trd] && (i_trd) < numTrd){
      // update position
      double theLot = lots_trd[i_trd];
      double theAmt = theLot * price_trd[i_trd];
      switch(bs_trd[i_trd]){
        case 0:
          bcl_pm[i_mkt] += theLot;
          sca_pm[i_mkt] += theAmt;
          bcn_pm[i_mkt] += 1;
        break;
        case 1:
          scl_pm[i_mkt] += theLot;
          bca_pm[i_mkt] += theAmt;
          scn_pm[i_mkt] += 1;
        break;
      }
      (i_trd)++;
    }
  return(i_trd);
}

void getPositionPL(
                  NumericVector bcl_pm,
                  NumericVector scl_pm,
                  NumericVector bca_pm,
                  NumericVector sca_pm,
                  NumericVector pl_pm,
                  NumericVector bid_mkt,
                  NumericVector mid_mkt,
                  NumericVector ask_mkt,
                  int i_mkt
                  ) {
  double netLots = bcl_pm[i_mkt] - scl_pm[i_mkt];
  double rate;
  if(netLots >= 0){
    // sell the netLots at bid_mkt
    rate = bid_mkt[i_mkt];
  } else {
    // buy the netLots at ask_mkt
    rate = ask_mkt[i_mkt];
  }
  // pl
  pl_pm[i_mkt] = bca_pm[i_mkt] - sca_pm[i_mkt] + netLots * rate;
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
  NumericVector price_trd= trd["price"];
  NumericVector bcl_pm   = pm["bCumLots"];
  NumericVector scl_pm   = pm["sCumLots"];
  NumericVector bca_pm   = pm["bCumAmts"];
  NumericVector sca_pm   = pm["sCumAmts"];
  NumericVector bcn_pm   = pm["bCustNums"];
  NumericVector scn_pm   = pm["sCustNums"];
  NumericVector bid_mkt = mkt["bid_rate"];
  NumericVector mid_mkt = mkt["mid_rate"];
  NumericVector ask_mkt = mkt["ask_rate"];
  NumericVector pl_pm    = pm["pl"];
  int numTrd = trd.nrows();
  int i_trd = 0;
  for(int i_mkt=1; i_mkt < mkt.nrows(); i_mkt++) {
    // update position: cumulative sum
    i_trd = updatePosition(bcl_pm, scl_pm, bcn_pm, scn_pm, bcn_pm, scn_pm,
                           time_mkt,
                           time_trd,
                           bs_trd,
                           lots_trd,
                           price_trd,
                           i_mkt,
                           i_trd,
                           numTrd,
                           bcl_pm[i_mkt-1],
                           scl_pm[i_mkt-1],
                           bca_pm[i_mkt-1],
                           sca_pm[i_mkt-1]
                           );
    // pl analysis
    getPositionPL(bcl_pm,
                  scl_pm,
                  bca_pm,
                  sca_pm,
                  pl_pm,
                  bid_mkt,
                  mid_mkt,
                  ask_mkt,
                  i_mkt
                  );
  }
  return(wrap(pl_pm));
}
