#ifndef Bits_H
#define Bits_H
#include <bitset>

using namespace std;
class Bits{
public:
	bitset<19> item;
public:
	Bits(){};
	Bits(int _item){
		item = _item;
	}

	int getitem(){
		return item.to_ulong();
	}

	bool operator > (const Bits & b) const {
		return this->item.to_ulong() > b.item.to_ulong();
	}
	bool operator < (const Bits & b) const {
		return this->item.to_ulong() < b.item.to_ulong();
	}
	bool operator >= (const Bits & b) const {
		return this->item.to_ulong() >= b.item.to_ulong();
	}
	bool operator <= (const Bits & b) const{
		return this->item.to_ulong() <= b.item.to_ulong();
	}
	bool operator != (const Bits & b) const{
		return this->item.to_ulong() != b.item.to_ulong();
	}
	bool operator == (const Bits & b) const{
		return this->item.to_ulong() ==b.item.to_ulong();
	}

	friend std::ostream& operator<<(std::ostream &out,const Bits &b){
		out<<b.item.to_ulong();
		return out;
	}
};

#endif
