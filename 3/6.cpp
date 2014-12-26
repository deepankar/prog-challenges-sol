#include <limits.h>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
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
typedef pair<string,string> PS;
typedef long long int lint;
typedef unsigned long long int luint;

#define FOR0(i, n) for(int i = 0; i < n; i++)

class Solver
{
   static bool sizesort(const string &s1, const string &s2)
   {
      if(s1.size() != s2.size()){
         return s1.size() < s2.size();
      }
      return s1 < s2;
   }
   void getPos(const PS &p1, const PS &p2, VS &pos)
   {
      pos.clear();
      pos.resize(8);
      int i = 0;
      const PS *p[2] = {&p1, &p2};
      FOR0(j, 2){
         pos[i++] = p[j]->first + p[1-j]->first;
         pos[i++] = p[j]->first + p[1-j]->second;
         pos[i++] = p[j]->second + p[1-j]->first;
         pos[i++] = p[j]->second + p[1-j]->second;
      }
      assert(i==8);
   }

   public:
   string solve(VS &bits)
   {
      int n = bits.size();
      sort(bits.begin(), bits.end(), sizesort);
      int s = bits[0].size() + bits[n-1].size();
      map<int,PS> smap;
      FOR0(i, bits.size()){
         PS &p = smap[bits[i].size()];
         if(p.first != bits[i] && p.second != bits[i]){
            if(p.first.empty()){
               p.first = bits[i];
            }else{
               assert(p.second.empty());
               p.second = bits[i];
            }
         }
      }
      VS pos;
      getPos(smap[bits[0].size()], smap[bits[n-1].size()], pos);
      FOR0(i, 8){
         if(pos[i].size() < s) continue;
         bool fail = false;
         int lastsize=-1;
         FOR0(b, bits.size()/2){
            VS pi;
            if(bits[b].size() == lastsize) continue;
            lastsize = bits[b].size();
            getPos(smap[bits[b].size()], smap[s-bits[b].size()], pi);
            if(find(pi.begin(), pi.end(), pos[i]) == pi.end()){
               fail = true;
               break;
            }
         }
         if(!fail){
            return pos[i];
         }
      }
      assert(0);
      return "";
   }
};

int main(int argc, char **argv)
{
   Solver slv;
   int tt;
   cin >> tt;
   string line;
   getline(cin, line);
   getline(cin, line);
   FOR0(t,tt){
      VS bits;
      while(getline(cin,line), cin.good() && line.size()){
         bits.push_back(line);
      }
      if(t) cout << endl;
      cout << slv.solve(bits) << endl;
   }
   return 0;
}
