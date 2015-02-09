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

#if 1
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

class State
{
   public:
      int ca;
      int cb;
      int i; //start index
      State(int ca, int cb, int i) : ca(ca), cb(cb), i(i) {}
      bool operator<(const State &st) const
      {
         if(ca != st.ca){
            return ca < st.ca;
         }
         if(cb != st.cb){
            return cb < st.cb;
         }
         return i < st.i;
      }
};

ostream& operator<<(ostream &os, const State &st)
{
   os << '(' << st.ca << ',' << st.cb << ';' << st.i << ')';
   return os;
}

class Solver
{
   int flen;
   const VI *cars;
   typedef map<State, int> cache_t;
   cache_t cache;
   int mxc(int ca, int cb, int i){
      if(ca < 0 || cb < 0){
         return -1;
      }
      if(i >= cars->size()){
         return 0;
      }
      State st(ca, cb, i);
      cache_t::iterator it = cache.find(st);
      if(it != cache.end()){
         return it->second;
      }
      int o1 = mxc(ca, cb - (*cars)[i], i+1);
      int o2 = mxc(ca - (*cars)[i], cb, i+1);
      int res = max(o1, o2) + 1;
//      cout << st << " = " << res << endl;
      cache[st] = res;
      return res;
   }
   public:
   void solve(int ferryLen, const VI &cars)
   {
      this->cars = &cars;
      flen = ferryLen;
      if(cars.size() == 0 || cars[0] > ferryLen){
         cout << "\n";
         return;
      }
      int maxc = mxc(flen-cars[0], flen, 1) + 1;
      cout << maxc << endl;
      State st(flen, flen, 0);
      FOR0(i, maxc){
         State o1(st.ca, st.cb - cars[i], i+1);
         State o2(st.ca - cars[i], st.cb, i+1);
         cache_t::iterator it1 = cache.find(o1);
         cache_t::iterator it2 = cache.find(o2);
         bool side;
         if((it1 == cache.end() && it2 == cache.end()) || it2 == cache.end()){
            side = true;
         }else if (it1 == cache.end()){
            side = false;
         }else{
            side =  it1->second > it2->second;
         }
         if(side){
            cout << "port\n";
            st = o1;
         }else{
            st = o2;
            cout << "starboard\n";
         }
      }
   }
};

int main(int argc, char **argv)
{
   int tt;
   cin >> tt;
   FOR0(t,tt){
      Solver slv;
      if(t) cout << endl;
      int ferryLen;
      cin >> ferryLen;
      ferryLen *= 100; //in cm
      int l;
      VI cars;
      while(cin >> l, l){
         cars.push_back(l);
      }
      slv.solve(ferryLen, cars);
   }
   return 0;
}
