//passed
#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;
typedef vector<int> VI;
typedef vector<bool> VB;
typedef vector<string> VS;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
	public:
   bool solve(const VI &in)
   {
      int n = in.size();
      VB diffs(n, false);
      for(int i = 0; i < n-1; i++){
         int d = abs(in[i] - in[i+1]);
         if(d > n-1) return false;
         diffs[d] = true;
      }
      for(int i = 1; i < n; i++){
         if(!diffs[i]) return false;
      }
      return true;
   }
};

int main(int argc, char **argv)
{
	Solver s;
	int n;
	while(cin.good()){
//      string line;
//      getline(cin, line);

      cin >> n;
      if(!cin.good()){
         return 0;
      }
      VI se;
      FOR0(i, n){
         int x;
         cin >> x;
         se.push_back(x);
      }
      //cout << line << endl;
		//cout << s.solve() << "\n";
      cout << (s.solve(se)? "Jolly" : "Not jolly") << endl;
	}
	return 0;
}
