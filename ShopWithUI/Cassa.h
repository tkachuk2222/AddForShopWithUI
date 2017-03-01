#pragma once
class Cass
{
public:
	Cass					() :cashInCass_(0) {};
//	friend Storage;
	void					addCash(double cash) { cashInCass_ += cash; }
	void					sellProd(double cash, int cnt);
	double					cashInCass() { return cashInCass_; };
	void					setCash(int n) { cashInCass_ = n; };
private:
	double					cashInCass_;
};
void Cass::sellProd(double cash, int cnt) {
	cashInCass_ += (cash*cnt*0.2)+ cash*cnt;
}