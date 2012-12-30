#include <Rcpp.h>
#include <iostream>
using namespace std;
using namespace Rcpp;

// [[Rcpp::export()]]
SEXP ex101(){
  vector<string> names(10);
  string str_array[2] = {"hoge", "fuga"};
  for(int i=0;i<2;i++){
    names.push_back(str_array[i]);
  }
  return(wrap(names));
}

// [[Rcpp::export()]]
SEXP ex102(){
  list<string> names;
  string str_array[2] = {"hoge", "fuga"};
  for(int i=0;i<2;i++){
    names.push_back(str_array[i]);
  }
  return(wrap(names));
}

// [[Rcpp::export()]]
SEXP ex103(){
  list<string> names;
  string str_array[3] = {"hoge", "fuga", "piyo"};
  for(int i=0;i<3;i++){
    names.push_back(str_array[i]);
  }
  list<string>::iterator itStart = names.begin();
  for(list<string>::iterator it=itStart; it!=names.end(); it++){
    cout << *it << " ";
  }
  return(wrap(names));
}

void viewListInt(list<int> l){
  for(list<int>::iterator it = l.begin(); it!=l.end(); it++){
    cout << *it << ",";
  }
  cout << "\n";
}

void ex104helper(list<int> l, vector<int> addNumbers, bool doView){
  for(unsigned int i=0; i<addNumbers.size(); i++){
    l.push_back(addNumbers[i]);
  }
  if(doView){
    cout << "inside ex104helper\n";
    viewListInt(l);
  }
}

// [[Rcpp::export]]
SEXP ex104(int size, bool doView){
  list<int> numbers;
  vector<int> addNums;// length = 0
  for(int i=0; i<size; i++){
    addNums.push_back(i*2);
  }
  cout << "addNumes.size()=" << addNums.size() << "\n";
  // add to list
  ex104helper(numbers, addNums, doView);
  cout << "in main \n";
  viewListInt(numbers);
  return(wrap(numbers));
}

void ex104_2helper(list<int>& l, const vector<int>& addNumbers, bool doView){
  for(unsigned int i=0; i<addNumbers.size(); i++){
    l.push_back(addNumbers[i]);
  }
  if(doView){
    cout << "inside ex104_2helper\n";
    viewListInt(l);
  }
}

// [[Rcpp::export]]
SEXP ex104_2(int size, bool doView){
  BEGIN_RCPP
  list<int> numbers;
  vector<int> addNums;// length = 0
  for(int i=0; i<size; i++){
    addNums.push_back(i*2);
  }
  // add to list
  ex104_2helper(numbers, addNums, doView);
  if(doView){
    cout << "in main \n";
    viewListInt(numbers);
  }
  return(wrap(numbers));
  END_RCPP
}

void ex105helper(list<int>& l, const vector<int>& addNumbers){
  for(unsigned int i=0; i<addNumbers.size(); i++){
    l.push_back(addNumbers[i]);
  }
}

void ex105viewListIntToEnd(list<int>::iterator& itBegin, list<int>& l){
  for(list<int>::iterator it = itBegin; it != l.end(); it++){
    cout << *it << " ";
  }
  cout << "\n";
}

// [[Rcpp::export]]
SEXP ex105(IntegerVector x, int repSize, bool doView){ // This doesn't work as I intend.
  BEGIN_RCPP
  list<int> numbers;
  vector<int> addNums;// length = 0
  for(int i=0; i<x.size(); i++){
    addNums.push_back(x[i]);
  }
  // add and view
  list<int>::iterator itBegin;
  for(int i=0; i<repSize; i++){
    itBegin = numbers.end();
    ex105helper(numbers, addNums);
    if(doView){
      ex105viewListIntToEnd(itBegin, numbers);
    }
  }
  return(wrap(numbers));
  END_RCPP
}

void ex105_2viewListIntToEnd(list<int>::iterator& it, list<int>& l){
  for( ; it != l.end(); it++){
    cout << *it << " ";
  }
  cout << "\n";
}

list<int>::iterator ex105_2helper(list<int>& l, const vector<int>& addNumbers){
  list<int>:: iterator itr = l.end();
  itr--;
  for(unsigned int i=0; i<addNumbers.size(); i++){
    l.push_back(addNumbers[i]);
  }
  itr++;
  return(itr);
}

// [[Rcpp::export]]
SEXP ex105_2(IntegerVector x, int repSize, bool doView){ // This works!
  BEGIN_RCPP
  list<int> numbers;
  vector<int> addNums;// length = 0
  for(int i=0; i<x.size(); i++){
    addNums.push_back(x[i]);
  }
  // add and view
  list<int>::iterator itBegin;
  for(int i=0; i<repSize; i++){
    itBegin = ex105_2helper(numbers, addNums);
    if(doView){
      ex105_2viewListIntToEnd(itBegin, numbers);
    }
    addNums[0] = i;
  }
  return(wrap(numbers));
  END_RCPP
}



/*** R
out104 <- ex104(3,doView=T)
out104_2 <- ex104_2(3, doView=T)

sizeNum <- 1000000
system.time(ex104(sizeNum,doView=F))
system.time(ex104_2(sizeNum, doView=F))

ex105(x=c(1:2), 2, doView=T)
ex105_2(x=c(1:2), 2, doView=T)

*/


