#ifndef MY_HASH
#define MY_HASH

#include <vector>

using namespace std;

template<class Gate>
class FEC_Key
{
public:
   FEC_Key(Gate* g):gate(g){}

   size_t operator() () const
   {
      size_t temp=gate->getHistory();
      if(temp%2==1)
         temp^=1;
      return temp;
   }

   bool operator == (const FEC_Key& k) const 
   {

      bool b=true,b0=true,b1=true,b00,b11;
      size_t result;
      vector<size_t>& h1 = gate->getHistorys();
      vector<size_t>& h2 = k.gate->getHistorys();

      for(int i=0,size=h1.size();i<size;i++)
      {
         result=(h1[0]^h2[0]);
         b00 = (result ==  0);
         b11 = (result == -1);
         if(!b00 && !b11)
            return false;
         if(b00 && !b0)
            return false;
         if(b11 && !b1)
            return false;
         b0=b00;
         b1=b11;
      }
      return true;
   }

private:
  Gate* gate;
};

template <class HashKey, class HashData>
class HashMap
{
typedef pair<HashKey, HashData> HashNode;

public:
   HashMap() : _numBuckets(0), _buckets(0) {}
   HashMap(size_t b) : _numBuckets(0), _buckets(0) { init(b); }
   ~HashMap() { reset(); }

   void init(size_t b) 
   {
      reset();
      _numBuckets = b; 
      _buckets = new vector<HashNode>[b]; 
   }
   
   void reset() 
   {
      _numBuckets = 0;
      if (_buckets) { delete [] _buckets; _buckets = 0; }
   }

   bool check(const HashKey& k, HashData& n) const 
   {
      size_t b = bucketNum(k);

      for (size_t i = 0, bn = _buckets[b].size(); i < bn; ++i)
         if (_buckets[b][i].first == k) 
         {
            n = _buckets[b][i].second;
            return true;
         }

      return false;
   }

   void insert(const HashKey& k, const HashData& d) 
   {
      size_t b = bucketNum(k);
      _buckets[b].push_back(HashNode(k, d));
   }

private:

   size_t                   _numBuckets;
   vector<HashNode>*        _buckets;

   size_t bucketNum(const HashKey& k) const { return (k() % _numBuckets); }

};


#endif 
