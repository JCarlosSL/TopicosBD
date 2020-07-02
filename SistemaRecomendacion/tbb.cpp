#include <boost/functional/hash.hpp>
#include <boost/timer/timer.hpp>
#include "tbb/concurrent_hash_map.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include <string>
#include <stdio.h>

using namespace std;
using namespace tbb;

template<typename K> 
struct MyHashCompare { 
    static size_t hash( const K& key )                  { return boost::hash_value(key); } 
    static bool   equal( const K& key1, const K& key2 ) { return ( key1 == key2 ); } 
}; 

// A concurrent hash table that maps strings to ints.
typedef concurrent_hash_map<string,int,MyHashCompare<string>> StringTable;
 
// Function object for counting occurrences of strings.
struct Tally {
    StringTable& table;
    Tally( StringTable& table_ ) : table(table_) {}
    void operator()( const blocked_range<string*> range ) const {
        for( string* p=range.begin(); p!=range.end(); ++p ) {
            StringTable::accessor a;
            table.insert( a, *p );
            a->second += 1;
            a.release();
        }
    }
};
 
const size_t N = 27000000;
 
string Data[N];

struct Filly {
  string& s;
  Filly(string& s): s(s) {}
  void operator()( const blocked_range<string*> range) const{
    for( string* p=range.begin(); p!=range.end(); ++p ) {
      *p = "abc";
    }
  }
}
 
void CountOccurrences() {
    // Construct empty table.
    StringTable table;
 
    // Put occurrences into the table
    parallel_for( blocked_range<string*>( Data, Data+N, 100000),
                  Tally(table) );
 
    // Display the occurrences
    for( StringTable::iterator i=table.begin(); i!=table.end(); ++i )
        printf(">%s-%d\n",i->first.c_str(),i->second);
}

int main(){
  boost::timer::auto_cpu_timer t;
  CountOccurrences();
}