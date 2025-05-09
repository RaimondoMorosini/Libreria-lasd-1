
#include <cmath>
#include <iostream>

using namespace std;

int f() { return 0; };

string g() { return string("This is a very long long long long long long string..."); }
string h() { return string("Another quite long long long long long long string..."); }

void arrayEpuntatori();
void slide1();
void slide2();
void slide3();
void slide4();

int main() {

   slide1();
   slide2();
   slide3();
   slide4();
   arrayEpuntatori();

  return 0;
}

void slide1(){

  // Slide 1

  bool bvar = true; // false
  cout << "Boolean variable: " << bvar << "; " << !bvar << endl;

  char cvar1 = 'A'; // 126
  // char cvar1 = 126;
  unsigned char cvar2 = 'Z'; // 126
  cout << "Char variable: " << cvar1 << "; " << endl;
  cout << "Unsigned char variable: " << cvar2 << "; " << endl;

  // short svar1 = 'A';
  short svar1 = -120; // 'A'
  unsigned short svar2 = -120; // 'A'
  cout << "Short variable: " << svar1 << "; " << endl;
  cout << "Unsigned short variable: " << svar2 << "; " << endl;

  // Other basic types: [unsigned] int, long (long int), long long (long long
  // int), float, double, long double. Synonyms for some standard libraries:
  // uint for unsigned int and ulong for unsigned long.

  uint uivar1 = pow(2, 32) - 120;
  uint uivar2 = -120;
  ulong ulvar1 = pow(2, 32) - 120;
  ulong ulvar2 = -120;
  cout << "Unsigned int variable: " << uivar1 << " == " << uivar2 << "; " << endl;
  cout << "Unsigned long variable: " << ulvar1 << " != " << ulvar2 << "; " << endl;

  float vecvar[3] = { 0.1, 2, 5.7 };
  // double vecvar[3] = { 0.1, 2, 5.7 };
  cout << "Double vector variable: ";
  for (uint i = 0; i < 3; i++) { cout << vecvar[i] << ' '; };
  cout << endl;

  long matvar[3][2] = { { 0, 1 }, { 2, 3 }, { 4, 5 } };
  cout << "Long matrix variable: " << endl;
  for (uint i = 0; i < 3; i++) { for (uint j = 0; j < 2; j++) { cout << matvar[i][j] << ' '; }; cout << endl; };

  const double pi = 3.141592;
  // pi = 3.141592;
  cout << "Double constant: " << pi << "; " << endl;

}

void slide2(){

  // // Slide 2
  //
  // char cvar = 'a';
  // char* cpvar = &cvar;
  // cout << "Char variable and its pointer: '" << cvar << "' == '" << *cpvar << "'; " << endl;
  // cvar++;
  // cout << "Char variable and its pointer: '" << cvar << "' == '" << *cpvar << "'; " << endl;
  //
  // int ivar = 'a';
  // int* ipvar = &ivar;
  // cout << "Int variable and its pointer: " << ivar << " == " << *ipvar << " != " << ipvar << "; " << endl;
  // ivar++;
  // cout << "Int variable and its pointer: " << ivar << " == " << *ipvar << " != " << ipvar << "; " << endl;
  //
  // const char ccon = 'a';
  // const char* cpcon = &ccon;
  // // char* cpcon = &ccon;
  // // const char* const cpcon = &ccon;
  // cout << "Char constant and its pointer: '" << ccon << "' == '" << *cpcon << "'; " << endl;
  // // ccon++;
  // cpcon++;
  // cout << "Char constant and its pointer: '" << ccon << "' (possibly)!= '" << *cpcon << "'; " << endl;
  // cpcon--;
  // cout << "Char constant and its pointer: '" << ccon << "' == '" << *cpcon << "'; " << endl;
  //
  // char cnew = 'z';
  // void* vptr = &cnew;
  // cout << "Char constant and its pointer: '" << cvar << "' == '" << *cpvar << "'; " << endl;
  // // cvar = *vptr;
  // // cvar = *((char*) vptr); // C-like cast
  // cvar = *(static_cast<char*>(vptr)); // C++ static cast
  // cout << "Char constant and its pointer: '" << cvar << "' == '" << *cpvar << "'; " << endl;
  // // cout << *vptr << ";" << endl;
  //
  // uint uivar = 25;
  // cout << "Unsigned integer variable: " << uivar << "; " << endl;
  // uivar = *((uint*) vptr); // C-like cast
  // // uivar = *(static_cast<uint*>(vptr)); // C++ static cast
  // // uivar = *((uint*) cpcon); // C-like cast
  // // uivar = *(static_cast<uint*>(cpcon)); // C++ static cast
  // cout << "Unsigned integer variable: " << uivar << "; " << endl;

}

void slide3(){

  // // Slide 3
  //
  // int ivarx = 0;
  // int& irvarx = ivarx;
  // cout << "Int variable and its reference: " << ivarx << " == " << irvarx << "; " << endl;
  // irvarx++;
  // cout << "Int variable and its reference: " << ivarx << " == " << irvarx << "; " << endl;
  //
  // //int& ivary = 0;
  // const int& ivary = 0;
  //
  // int ivarz = f();
  // // int& ivarz = f();

}

void slide4(){

  // // Slide 4
  //
  // string stringa1 = g(); // Copia del valore.
  // // string& stringa1 = g(); // Riferimento lvalue a un rvalue (valore temporaneo). Errato!
  // // string&& stringa1 = g(); // Riferimento rvalue.
  // // string stringa1 = std::move(g()); // Spostamento del valore.
  //
  // cout << "1) " << stringa1 << endl;
  //
  // // string&& stringa2 = h();
  // //
  // // cout << "2) " << stringa2 << endl;
  // //
  // // stringa1 = std::move(stringa2);
  // //
  // // cout << "3) " << stringa1 << endl;
  // // cout << "4) " << stringa2 << endl;

}
void arrayEpuntatori(){
   cout << "Casi in cui array e puntatori hanno comportamenti diversi" << endl;
   cout << "1) Dichiarazione dell'array" << endl;
   double primoVettore[] { 0.1, 0.2, 0.3, 0.4 };
   double *primoPuntatore;

   cout << primoVettore[2] << endl;
   // cout << primoPuntatore[2] << endl;
   
   cout << "2) Operatore sizeof " << sizeof(primoVettore) << " diverso da " << sizeof(primoPuntatore) << endl;
   cout << "3) Operatore &amp;" << endl;
}
