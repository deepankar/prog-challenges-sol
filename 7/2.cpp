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

class Solver
{
   public:
   int mpow(int x, int p, int m)
   {
      if(p == 0) return 1;
      lint res;
      res = mpow(x, p/2, m);
      res = res*res;
      if(p & 1){
         res *= x;
      }
      res = res % m;
      return res;
   }
   bool isPrime(int n)
   {
      int sq = sqrt(n);
      for(int i = 2; i <= sq; i++){
         if(n % i == 0){
            return false;
         }
      }
      return true;
   }
   bool solve(int n)
   {
      if(isPrime(n)) return false;
      for(int a = 2; a < n; a++){
         if(mpow(a, n, n) != a){
            return false;
         }
      }
      return true;
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int n;
   while(cin >> n, n){
      if(slv.solve(n)){
         cout << "The number " << n << " is a Carmichael number.\n";
      }else{
         cout << n << " is normal.\n";
      }
   }
   return 0;
}
