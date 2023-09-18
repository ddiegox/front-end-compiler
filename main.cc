#include <iostream>
using namespace std;


// putchard - putchar that takes a double and returns 0.
extern "C"  double putchard(double X) {
  fputc((char)X, stderr);
  return 0;
}

extern "C" double prova(double arr[], double size) {
  for(int i = 0; i < size; i++) {
    cout<<arr[i]<<endl;
  }
  return 0;
}

extern "C" double test(double a) {
  cout<<"Il numero è " <<a<<endl;
  return 0;
}

// extern "C" {
//   double func(double);
// }

 int main() {
    double x[] = {41, 42, 43, 44};
   for(int i = 0; i < 0; i++) {
     cout<<"hello"<<endl;
   }

   
   double x;
   cout<<"Inserisci x: "<<endl;

   
   cin>>x;
   cout<<"Il valore è "<<func(x)<<endl;

   
   func(x);
   return 0;
}
