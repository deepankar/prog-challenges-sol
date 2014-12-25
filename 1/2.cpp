//done
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
   void incrNeigh(char *f, int m, int n, int r, int c){
      for(int i = -1; i<=1; i++){
         for(int j =-1; j<=1; j++){
            incr(f, m, n, r+i,c+j);
         }
      }
   }
   void incr(char *f, int m, int n, int r, int c){
      if(r < 0 || c < 0 || r>=n || c>=m) return;
      if(f[r*m+c] == -1) return;
      f[r*m+c]++;
   }
   void printField(const char*f, int m, int n){
      FOR0(r, n){
         FOR0(c,m){
            if(f[r*m+c] == -1){
               cout << '*';
            }else{
               cout << (int)f[r*m+c];
            }
         }
         cout << endl;
      }
   }
	public:
   void solve(const VS&mines)
   {
      int m = mines[0].size();
      int n = mines.size();
      char *of = new char[m*n];
      memset(of, 0, m*n);
      FOR0(r, n){
         FOR0(c, m){
            if(mines[r][c] == '*'){
               of[r*m+c] = -1;
               incrNeigh(of, m, n, r, c);
            }
         }
      }
      printField(of, m, n);
   }
};

int main(int argc, char **argv)
{
	Solver s;
	int m,n;
   int i=0;
	while(cin.good()){
      i++;
      cin >> n >> m;
      if(n == 0) return 0;
      if(i>1) cout <<endl;
      string line;
      VS f;
      FOR0(l, n){
         string row;
         cin >> row;
         f.push_back(row);
      }
      cout << "Field #" << i <<":\n";
      s.solve(f);
      //cout << line << endl;
	}
	return 0;
}
