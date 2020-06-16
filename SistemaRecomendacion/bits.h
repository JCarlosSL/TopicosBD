#ifndef Bits_H
#define Bits_H
#include <bitset>

class Bits{

public:
	std::bitset<19> item;
	//float rating;

	Bits(){};
	/*Bits(int _item,float _rating){
		item = _item;
		rating = _rating;
	}*/
	Bits(int _item){
		item = _item;
		//rating=0;
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
