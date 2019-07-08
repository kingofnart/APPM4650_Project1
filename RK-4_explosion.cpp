#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

double f(double x, double y);
double y(double t);
void RK4(double a, double b, int N, double alpha);

int main(){
  string input;
  cout << "Enter the first endpoint: ";
  getline(cin, input);
  double a = stod(input);
  cout << "Enter the second endpoint: ";
  getline(cin, input);
  double b = stod(input);
  cout << "Enter number of discrete points: ";
  getline(cin, input);
  int N = stoi(input);
  cout << "Enter an initial condition: ";
  getline(cin, input);
  double alpha = stod(input);
  cout << endl << endl;
  RK4(a, b, N, alpha);
  return 0;
}

double f(double x, double y){
  return 1/(exp(x)-x);
}

double y(double t){
  return t;
}

void RK4(double a, double b, int n, double alpha){
  ofstream outFile;
  outFile.open("exp_data.txt");
  if(outFile.is_open()){
    double k1 = 0, k2 = 0, k3 = 0, k4 = 0, ex = 0;
    double h = (b-a)/n, t = a, w = alpha, wPrev = alpha;
    cout << "\t\tRunge-Kutta Order Four" << endl;
    cout << "\t\t\tExplosion!" << endl << endl;
    cout << "sigma\t|  APROX soln (early)\t|  sigma(theta) (RK-4) \t|\tError\t\t|  delta sigma" << endl;
    cout << "--------|-----------------------|-----------------------|-----------------------|----------------" << endl;
    cout << t << "\t|\t" << y(t) << "\t\t|\t" << w << "\t\t|\t" << abs(y(t)-w) << "\t\t|\t" << abs(wPrev-w) << endl;
    outFile << w << "\n";
    for(int i=1; i<=n; i++){
      k1 = h*f(t,w);
      k2 = h*f(t+h/2,w+k1/2);
      k3 = h*f(t+h/2,w+k2/2);
      k4 = h*f(t+h,w+k3);
      wPrev = w;
      w = w+(k1+2*(k2+k3)+k4)/6;
      t = t+h;
      cout << fixed << setprecision(1) << t << "\t|\t" << setprecision(7) << y(t) << "\t|\t" << w << "\t|\t" << abs(y(t)-w) << "\t|\t" << abs(wPrev-w) << endl;
      outFile << w << "\n";
    }
  }
  outFile.close();
}
