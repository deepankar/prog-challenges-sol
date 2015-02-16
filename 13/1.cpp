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
typedef pair<double,double> PD;
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
   double dist_sq(const Point &p1, const Point &p2){
      return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
   }
   public:
   void solve(const Point &dog, const Point &g, const vector<Point> &pts)
   {
      std::cout.precision(3);
      std::cout << fixed;
      int n = pts.size();
      FOR0(i, n){
         double dd = dist_sq(pts[i], dog);
         double dg = dist_sq(pts[i], g);
         if(dd >= 4*dg){
            cout << "The gopher can escape through the hole at (" << pts[i].x <<',' << pts[i].y << ").\n";
            return;
         }
      }
      cout << "The gopher cannot escape.\n";
   }
};

int main(int argc, char **argv)
{
   int nholes;
   while(cin >> nholes && cin.good()){
      Solver slv;
      Point gopher, dog;
      cin >> gopher.x >> gopher.y;
      cin >> dog.x >> dog.y;
      vector<Point> pts(nholes);
      FOR0(i,nholes){
         cin >> pts[i].x >> pts[i].y;
      }
      slv.solve(dog, gopher, pts);
   }
   return 0;
}
