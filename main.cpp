#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ifstream customerFile("data4customer.txt");
  ifstream moviesFile("data4movies.txt");
  ifstream transactionsFile("data4commands.txt");

  if (!customerFile)                
      cout << "Customer file cannot be oppened" << endl;
  if (!moviesFile)                   
      cout << "Movie file cannot be oppened" << endl;
  if (!transactionsFile)             
      cout << "Transaction file cannot be oppened" << endl;
}
