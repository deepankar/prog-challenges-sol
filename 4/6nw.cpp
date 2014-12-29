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

class Record
{
   public:
   string l;
   int t; //mins
   bool entry;
   lint km;
   bool operator<(const Record &r) const{
      if(l != r.l){
         return l < r.l;
      }
      return t < r.t;
   }
   int hour() const{
      int x = t % (24*60);
      x = x / 60;
      assert(x >=0 && x <24);
      return x;
   }
};

class Solver
{
   public:
   void solve(vector<Record> &r, const VI&t)
   {
      sort(r.begin(), r.end());
      map<string, lint> bills;
      if(r.empty()){
         return;
      }
#if 0
      FOR0(i, r.size()-1){
         if(!r[i].entry) continue;
         if(r[i+1].entry) continue;
         lint d = llabs(r[i].km - r[i+1].km);
         int rate = t[r[i].hour()];
         lint bill = rate *d + 100;
         bills[r[i].l] += bill;
      }
#else
      int ei = -1;
      FOR0(i, r.size()){
         if(r[i].entry && ei <0){
            ei = i;
            continue;
         }
         if(!r[i].entry && ei >= 0){
            lint d = llabs(r[ei].km - r[i].km);
            int rate = t[r[ei].hour()];
            lint bill = rate *d + 100;
            bills[r[i].l] += bill;
            ei = -1;
         }
      }
#endif
      std::cout.precision(2);
      std::cout << fixed;
      for(map<string, lint>::const_iterator it = bills.begin(); it != bills.end(); it++){
         cout << it->first << " $" << (double)(200+it->second)/100 << endl;
      }
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int tt;
   cin >> tt;
   FOR0(t,tt){
//      map<string, bool> emap;
      if(t) cout << endl;
      VI toll;
      FOR0(i,24){
         int x;
         cin >> x;
         toll.push_back(x);
      }
      string line;
      getline(cin, line);
      vector<Record> rec;
      while(getline(cin, line), line.size() && cin.good()){
         istringstream ss(line);
         Record r;
         ss >> r.l;
         int x,d,h,m;
         ss >> x;
         char c;
         ss >> c; assert(c==':');
         ss >> d;
         ss >> c; assert(c==':');
         ss >> h;
         ss >> c; assert(c==':');
         ss >> m;
         r.t = m+ h*60 + d*24*60;
         string s;
         ss >> s;
         if(s == "enter"){
            r.entry = true;
         }else{
            r.entry = false;
         }
         ss >> r.km;
//         if(r.entry && emap[r.l]) continue;
 //        if(!r.entry && !emap[r.l]) continue;
//         emap[r.l] = r.entry;
         rec.push_back(r);
      }
      slv.solve(rec,toll);
   }
   return 0;
}
