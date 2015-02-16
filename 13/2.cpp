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
typedef vector<vector<int> > VVI;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Point
{
   public:
   double x,y;
};

class Solver
{
   public:
   double solve(const Point &p1, const Point &p2, const double r)
   {
      double d2_sq = p1.x*p1.x + p1.y*p1.y;
      double d4_sq = p2.x*p2.x + p2.y*p2.y;
      double d2 = sqrt(d2_sq);
      double d4 = sqrt(d4_sq);
      double d1_sq = d2_sq - r*r;
      double d3_sq = d4_sq - r*r;
      double d1 = sqrt(d1_sq);
      double d3 = sqrt(d3_sq);
      double direct_sq = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
      double direct = sqrt(direct_sq);
      double cosA = (d2_sq + d4_sq - direct_sq)/(2*d2*d4);
      double A = acos(cosA);
      double a1 = atan(d1/r);
      double a2 = atan(d3/r);
      double mid = A - a1 - a2;
      double total = mid*r + d1 + d3;
      return mid < 0 ? direct : total;
   }
};

int main(int argc, char **argv)
{
   int tt;
   cin >> tt;
   std::cout.precision(3);
   std::cout << fixed;
   FOR0(t,tt){
      Solver slv;
      Point p1, p2;
      double r;
      cin >> p1.x >> p1.y >> p2.x >> p2.y >> r;
      cout << slv.solve(p1,p2,r) << endl;
   }
   return 0;
}
