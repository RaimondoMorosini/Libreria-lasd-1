/*
 * Really simple example toshow that all classes come with a copy constructor and a copy assignment
 */


#include<iostream>
using namespace std;

class Simple{
   private:
      int attributo;
};

int main(){
   Simple A, B;  // sullo stack
   A = B;
   Simple *C = new Simple; // sulla heap

   return 0;
}
