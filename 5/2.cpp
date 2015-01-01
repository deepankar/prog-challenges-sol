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
typedef unsigned int uint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
   void getDigits(uint n, VI &v){
      v.clear();
      while(n){
         v.push_back(n %10);
         n = n/10;
      }
   }
   bool isPalindrome(const VI &d){
      int i = 0;
      int j = d.size() -1;
      while(i < j){
         if(d[i] != d[j]) return false;
         i++;
         j--;
      }
      return true;
   }
   uint getNum(const VI &d){
      uint n = 0;
      int m = 1;
      FOR0(i, d.size()){
         n += m*d[i];
         m *= 10;
      }
      return n;
   }
   public:
   int solve(uint n, uint &p)
   {
      VI digits;
      int c = 0;
      while(getDigits(n,digits), !isPalindrome(digits)){
         reverse(digits.begin(), digits.end());
         int r = getNum(digits);
         n += r;
         c++;
         if(c > 1000) return -1;
      }
      p = n;
      return c;
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int tt;
   cin >> tt;
   FOR0(t,tt){
      uint n, p;
      cin >> n;
      cout << slv.solve(n, p);
      cout << ' ' << p << endl;
   }
   return 0;
}
