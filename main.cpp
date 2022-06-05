#include <iostream>
#include <fstream>

using namespace std;

int main(){

   //Open files
   ifstream customerFile("data4customers.txt");
   if(!customerFile) {
      cout << "Error, data4customers.txt not found";
      return 1;
   }

   ifstream movieFile("data4movies.txt");
   if(!customerFile) {
      cout << "Error, data4movies.txt not found";
      return 1;
   }

   ifstream commandFile("data4commands.txt");
   if(!customerFile) {
      cout << "Error, data4commands.txt not found";
      return 1;
   }

   
}
