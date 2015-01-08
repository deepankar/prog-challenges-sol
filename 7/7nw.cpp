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
#endif

#if 1
#define INS \
{ \
   static int calls; \
   calls++; \
   cout << __FUNCTION__ << ":" << calls << endl; \
}
#else
#define INS 
#endif
template<class T>
void pv(const vector<T> &v){
   if(!v.size()){
      cout <<"{}\n";
      return;
   }
   cout << "{";
   FOR0(i,v.size()-1){
      cout << v[i] <<", ";
   }
   cout << v[v.size()-1] << "}\n";
}

class Solver
{

   /* This function return the gcd of a and b followed by
    *     the pair x and y of equation ax + by = gcd(a,b)*/
   pair<int, pair<int, int> > extendedEuclid(int a, int b) {
      if(a > b){
         pair<int, pair<int, int> > res = extendedEuclid(b, a);
         swap(res.second.first, res.second.second);
         return res;
      }
      int x = 1, y = 0;
      int xLast = 0, yLast = 1;
      int q, r, m, n;
      while(a != 0) {
         q = b / a;
         r = b % a;
         m = xLast - q * x;
         n = yLast - q * y;
         xLast = x, yLast = y;
         x = m, y = n;
         b = a, a = r;
      }
      return make_pair(b, make_pair(xLast, yLast));
   }
   int modInverse(int a, int m) {
      return (extendedEuclid(a,m).second.first + m) % m;
   }
   int gcd(int a, int b)
   {
      return extendedEuclid(a,b).first;
   }

   /**
    * Solve for x in:
    * ax=b (mod n)
    */
   lint minsolve(lint a, lint b, lint n)
   {
      lint gcd_an = gcd(a, n);
      lint g = gcd(gcd_an, b);
      if(g > 1){
         return minsolve(a/g, b/g, n/g);
      }
      if(gcd_an == 1){
         return (n+modInverse(a, n)*b) % n;
      }
      return -1;
   }
   public:
   void solve(lint n, lint c1, lint n1, lint c2, lint n2)
   {
      lint x=-1,y=-1;
      if(c2 > c1){
         y = minsolve(n2, n, n1);
         if(y != -1){
            x = (n-y*n2)/n1;
            assert((n-y*n2)%n1 == 0);
         }
      }else{
         x = minsolve(n1, n, n2);
         if(x != -1){
            y = (n-n1*x)/n2;
            assert((n-n1*x)%n2 == 0);
         }
      }
      if(x <0 || y < 0){
         cout << "failed\n";
      }else{
         cout << x << " " << y << endl;
      }
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int n;
   while(cin >> n, n){
      int c1, n1, c2, n2;
      cin >> c1 >> n1;
      cin >> c2 >> n2;
      slv.solve(n,c1,n1,c2,n2);
   }
   return 0;
}
