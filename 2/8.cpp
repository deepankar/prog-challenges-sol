#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <map>
#include <hash_map>
#include <algorithm>
#include <numeric>
#include <string>
#include <stdint.h>
#include <sstream>
using namespace std;
using namespace __gnu_cxx;
typedef uint8_t u8;
typedef vector<u8> VU8;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<bool> VB;
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

class Move
{
   uint8_t nums[6];
   public:
   Move(const uint8_t* moves)
   {
      memcpy(nums, moves, 5);
      sort(nums, nums+5);
      nums[5] = 0;
   }
   int score(uint8_t st) const
   {
      switch(st){
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
            {
               int s = 0;
               FOR0(i,5){
                  if(nums[i] == st+1){
                     s+=nums[i];
                  }
               }
               return s;
            }
         case 6:
            return accumulate(nums, nums+5,0);
         case 7:
            if(nums[0] == nums[2] ||
                  nums[1] == nums[3] ||
                  nums[2] == nums[4]){
               return accumulate(nums, nums+5, 0);
            }else{
               return 0;
            }
         case 8:
            if(nums[0] == nums[3] ||
                  nums[1] == nums[4]){
               return accumulate(nums, nums+5, 0);
            }else{
               return 0;
            }
         case 9:
            if(nums[0] == nums[4]){
               return 50;
            }else{
               return 0;
            }
         case 10:
            {
               char s1[] = {1,2,3,4,0};
               char s2[] = {2,3,4,5,0};
               char s3[] = {3,4,5,6,0};
               if(strstr((char*)nums,s1)||
                     strstr((char*)nums,s2)||
                     strstr((char*)nums,s3)){
                  return 25;
               }else{
                  return 0;
               }
            }
         case 11:
            {
               char s1[] = {1,2,3,4,5,0};
               char s2[] = {2,3,4,5,6,0};
               if(strstr((char*)nums,s1)||
                     strstr((char*)nums,s2)){
                  return 35;
               }else{
                  return 0;
               }
            }
         case 12:
            if((nums[0] == nums[2] && nums[3] == nums[4]) ||
                  (nums[0] == nums[1] && nums[2] == nums[4])){
               return 40;
            }else{
               return 0;
            }
      }
      assert(0);
      return -1;
   }
};

typedef vector<Move> Moves;
class Key
{
   public:
      ushort set;
      short bontgt;
      ushort st;
      Key(ushort set, ushort st, short bontgt) : set(set), bontgt(bontgt), st(st) {
         if(this->bontgt < 0){
            this->bontgt = -1;
         }
      }
      Key(): set(0xdead), bontgt(-1), st(0xdead) {}
      bool operator==(const Key &k) const
      {
         return set == k.set &&
                bontgt == k.bontgt &&
                st == k.st;
      }
};

      struct khash
      {
         std::size_t operator()(const Key& k) const
         {
            return k.set*abs(k.bontgt)*k.st;
         }
      };
class Solver
{
   class Result
   {
      public:
      int val;
      ushort moveScore;
      ushort cat;
      Key nextkey;
      Result(int val, ushort moveScore, ushort cat) : val(val), moveScore(moveScore), cat(cat) {}
      Result() : val(-1), moveScore(0xdead), cat(0xdead) {}
      bool operator<(const Result &r) const
      {
         return cat < r.cat;
      }
   };

   typedef hash_map<Key, Result, khash> htype;
   int getMax(const Moves &moves, ushort st, ushort set, short bontgt, htype &cache)
   {
      if(st >= moves.size() || !set){
         assert(st == moves.size() && !set);
         return bontgt>0 ? -1:0;
      }
      Key k(set, st, bontgt);
      htype::const_iterator it;
      if((it = cache.find(k)) != cache.end()){
         return it->second.val;
      }
      const Move &m = moves[st];
      Result res;
      FOR0(i, 13){
         if(set & (1<<i)){
            int ms = m.score(i);
            assert(ms < 200);
            ushort rset = set & ~(1<<i);
            int rtgt = i<6? bontgt - ms : bontgt;
            int rs = getMax(moves, st+1, rset, rtgt, cache);
            //cout <<"=" << i << ":" << ms << ' ' << rs << endl;
            if(ms + rs > res.val && rs>=0){
               res.val = ms+rs;
               res.moveScore = ms;
               res.cat = i;
               res.nextkey = Key(rset,st+1, rtgt);
            }
         }
      }
      cache[k] = res;
      return res.val;
   }
	public:
   void solve(const Moves &moves)
   {
      htype cachebon;
      int bon = getMax(moves,0,0x1fff, 63, cachebon);
      Key kb(0x1fff, 0, 63);
      htype cache_nobon;
      int nbon = getMax(moves,0,0x1fff, 0, cache_nobon);
      Key knb(0x1fff, 0, 0);
      htype *cache;
      const Key *k;
      int bonus = 0;
      if(bon + 35 > nbon){
         cache = &cachebon;
         k = &kb;
         bonus = 35;
      }else{
         cache = &cache_nobon;
         k = &knb;
      }
      int s = bonus;
      vector<Result> res;
      FOR0(i, 13){
         htype::const_iterator it = cache->find(*k);
         assert(it != cache->end());
         res.push_back(it->second);
         s+= it->second.moveScore;
         k = &(it->second.nextkey);
      }
      sort(res.begin(), res.end());
      FOR0(i,13){
         cout << res[i].moveScore << ' ';
      }
      cout << bonus << ' ' << s << endl;
   }
};

int main(int argc, char **argv)
{
	Solver slv;
	while(cin.good()){
      vector<Move> moves;
      u8 n[5];
      FOR0(i, 13){
         FOR0(j, 5){
            int x;
            cin >> x;
            n[j] = x;
            if(!cin.good()){
               return 0;
            }
         }
         Move m(n);
         moves.push_back(m);
      }
      slv.solve(moves);
	}
	return 0;
}
