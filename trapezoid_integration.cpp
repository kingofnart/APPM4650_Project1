#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

double f(double x);

int main(){
  int a = 0, b = 1;
  string input;
  cout << "Enter a tolerance: ";
  getline(cin, input);
  double e = stod(input), sum = 0, q = (f(a)+f(b))/2;
  cout << "Integral from " << a << " to " << b << ": " << q << endl;
  a++, b++;
  sum += q;
  cout << "Enter max x value: ";
  getline(cin, input);
  int n = stoi(input);
  while(q>e && a<n){
    q = (f(a)+f(b))/2;
    cout << "Integral from " << a << " to " << b << ": " << q << endl;
    a++, b++;
    sum += q;
  }
  if(a==n){
    cout << "integral didn't converge less than " << e << " before x = " << n << endl;
  }
  else{
    cout << "Intergral converged to " << sum << endl;
    ofstream outFile;
    outFile.open("sigma_exp.txt");
    if(outFile.is_open()){
      cout << "file opened" << endl;
      outFile << sum;
      outFile.close();
    }
  }
}

double f(double x){
  return 1/(exp(x)-x);
}
