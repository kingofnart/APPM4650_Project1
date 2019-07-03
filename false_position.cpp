#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

struct NthRoot{
  float aValue;
  float bValue;
  float cValue;
  int num;
  NthRoot* next = nullptr;
};

//r1 is xn-1 r2 is xn
bool RelChange(float r1, float r2, float e);
bool AbsChange(float r1, float r2, float e);
float f(float x);
void deleteList(NthRoot* head);

int main(){
  string nInput, aInput, bInput, eInput;
  int n = 0, i = 1;
  float a = 0, b = 0, e = 0; //xn is the nth root estimate, xn1=x_(n-1), xn2=x_(n-2)
  cout << "Enter a first initial guess: ";
  getline(cin, aInput);
  a = stof(aInput);
  cout << "Enter a second initial guess: ";
  getline(cin, bInput);
  b = stof(bInput);
  NthRoot *prevNode = new NthRoot;
  prevNode->aValue = a;
  prevNode->bValue = b;
  prevNode->cValue = b-f(b)*(b-a)/(f(b)-f(a));
  prevNode->num = 0;
  NthRoot *head = prevNode;
  cout << "Enter max error: ";
  getline(cin, eInput);
  e = stof(eInput);
  if(f(a) == 0){
    cout << "Found root after 0 iterations! Lucky guess... Root: " << a << endl;
  }
  else if(f(b) == 0){
    cout << "Found root after 0 iterations! Lucky guess... Root: " << b << endl;
  }
  else if(f(prevNode->cValue) == 0){
    cout << "Found root after 0 iterations! Lucky guess... Root: " << prevNode->cValue << endl;
  }
  else if(f(a)*f(b) > 0){
    if(a > b){
      cout << "(" << b << "," << a << ") does not contain a root." << endl;
    }
    else{
      cout << "(" << a << "," << b << ") does not contain a root." << endl;
    }
  }
  else{
    cout << "Enter number of iterations: ";
    getline(cin, nInput);
    n = stoi(nInput);
    while(i <= n){
      NthRoot *currNode = new NthRoot;
      currNode->num = i;
      if(f(prevNode->aValue)*f(prevNode->cValue) > 0){ //(c,b) has root, throw away (a,c)
        currNode->aValue = prevNode->cValue;
        currNode->bValue = prevNode->bValue;
      }
      else if(f(prevNode->aValue)*f(prevNode->cValue) < 0){ //(a,c) has root, throw away (c,b)
        currNode->aValue = prevNode->aValue;
        currNode->bValue = prevNode->cValue;
      }
      currNode->cValue = currNode->bValue-f(currNode->bValue)*(currNode->bValue-currNode->aValue)/(f(currNode->bValue)-f(currNode->aValue));
      prevNode->next = currNode;
      if(f(currNode->cValue) == 0 || RelChange(prevNode->cValue, currNode->cValue, e)){
        cout << "Found root after " << i << " iterations. Root: " << currNode->cValue << endl;
        ofstream outFile;
        outFile.open("theta_fiz.txt");
        if(outFile.is_open()){
          outFile << currNode->cValue << "\n";
          outFile.close();
        }
        break;
      }
      prevNode = currNode;
      i++;
    }
    if(i > n){
      cout << "Method of False Position failed after " << n << " iterations." << endl;
    }
    cout << endl << "**Method of False Position Table**" << endl;
    NthRoot *tmp = head;
    if(i<11){
      while(tmp != nullptr){
        cout << "Iteration: " << tmp->num << "\ta: " << tmp->aValue << "\tb: " << tmp->bValue << "\tc: " << tmp->cValue << endl;
        tmp = tmp->next;
      }
    }
    else{
      for(int p=0; p<5; p++){
        cout << "Iteration: " << tmp->num << "\ta: " << tmp->aValue << "\tb: " << tmp->bValue << "\tc: " << tmp->cValue << endl;
        tmp = tmp->next;
      }
      while(tmp->num < i-4){
        tmp = tmp->next;
      }
      cout << "..." << endl;
      for(int u=0; u<5; u++){
        cout << "Iteration: " << tmp->num << "\ta: " << tmp->aValue << "\tb: " << tmp->bValue << "\tc: " << tmp->cValue << endl;
        tmp = tmp->next;
      }
    }
    deleteList(head);
  }
}

bool RelChange(float r1, float r2, float e){
  if(abs((r2-r1)/r1) < e){
    //cout << "RelChange satisfied! (r2-r1)/r2: " << (r2-r1)/r2 << endl;
    return true;
  }
  return false;
}

bool AbsChange(float r1, float r2, float e){
  if(abs((r2-r1)) < e){
    //cout << "AbsChange satisfied! r2-r1: " << r2-r1 << endl;
    return true;
  }
  return false;
}

float f(float x){
  return exp(x)/3-x;
}

void deleteList(NthRoot* head){
  NthRoot *tmp = head->next, *prev = head;
  while(tmp != nullptr){
    delete prev;
    prev = tmp;
    tmp = tmp->next;
  }
  delete prev;
}
