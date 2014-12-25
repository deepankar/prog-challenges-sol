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
typedef vector<string> VS;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
   int getLen(int x){
      int n = 1;
      while(x!= 1){
         if(x&1){
            x = 3*x + 1;
         }else{
            x = x >> 1;
         }
         n++;
      }
      return n;
   }
	public:
   int solve(int a, int b)
   {
      int mx = 1;
      if(b<a){
         int t = a;
         a = b;
         b = t;
      }
      for(int i = a; i <=b; i++){
         mx = max(mx, getLen(i));
      }
      return mx;
   }
};

int main(int argc, char **argv)
{
	Solver s;
	int m,n;
	while(cin.good()){
      string line;
      cin >> m >> n;
      if(!cin.good()){
         return 0;
      }
      cout << m << " " << n << " " << s.solve(m,n) << endl;
      //cout << line << endl;
		//cout << s.solve() << "\n";
      //s.solve();
	}
	return 0;
}
