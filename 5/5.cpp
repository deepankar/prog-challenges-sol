#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <stdint.h>
#include <sstream>
using namespace std;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<bool> VB;
typedef pair<int,int> PI;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)
#if 0
#define C cout
#else
#include <fstream>
ofstream C("/dev/null");
#define INS 
#endif

class Solver
{
   typedef map<uint, bool> win_t;
   win_t win;
   bool isWinningPos(luint n, luint t, int rec){
      if(9*n >= t) return true;
      win_t::iterator it;
      if((it = win.find(n)) != win.end()){
         C<<rec<<": " << n << " in cache="<<it->second << endl;
         return it->second;
      }
      C<<rec<<": " << "Checking for " << n << endl;
      for(int i = 9; i >=2; i--){
         luint r = i*n;
         if(!isWinningPos(r,t,rec+1)){
            C <<rec<<": "<< n << "->" << r << " true\n";
            win[n] = true;
            return true;
         }
      }
      C<<rec<<": " << n << " false\n";
      win[n] = false;
      return false;
   }
   public:
   bool solve(uint n)
   {
      win.clear();
      return isWinningPos(1, n, 0);
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   uint n;
   while(cin >> n, cin.good()){
      cout << (slv.solve(n)? "Stan wins." : "Ollie wins.") << endl;
   }
   return 0;
}
