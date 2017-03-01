#pragma once


using namespace std;

class Products
{
public:
	Products					(int cnt, string name, int term, double cost) : cnt_(cnt), name_(name), term_(term), cost_(cost) {};
	virtual void				show() {
		cout << cnt_ << "\t" << name_ << "\t" << term_ << "\t" << cost_ << "\t";
	}
	virtual void				getProd(int cnt) { cnt_ -= cnt; }
	virtual double				getPrice() { return cost_; };
	virtual void				plusToCnt(int n) { cnt_ += n; };
	virtual int					getCnt() { return cnt_; }
	virtual string				getName() { return name_; }
protected:
	int cnt_;
	string name_;
	int term_;
	double cost_;
};

class Eating :public Products {
public:
	Eating				(int cnt, string name, int term, double cost) :Products(cnt, name, term, cost) {};
	virtual void				show()override { Products::show(); /*cout << endl;*/ }
	virtual void				plusToCnt(int n) override { Products::plusToCnt(n); }
	virtual int					getCnt() override { return Products::getCnt(); }
	virtual string				getName() override { return Products::getName(); }
protected:
};

class Drinking :public Products {
public:
	Drinking				(int cnt, string name, int term, double cost) :Products(cnt, name, term, cost) {};
	virtual void				show()override { Products::show(); /*cout << endl;*/ }
	virtual void				plusToCnt(int n)override { Products::plusToCnt(n); }
	virtual int					getCnt() override { return Products::getCnt(); }
	virtual string				getName() override { return Products::getName(); }
protected:
};

class Cookies :public Eating {
public:
	Cookies				(int cnt, string name, int term, double cost, string kind) :Eating(cnt, name, term, cost), kind_(kind) {};
	virtual void				show()override { Eating::show(); cout << kind_; }
	virtual void				plusToCnt(int n) override { Products::plusToCnt(n); }
	virtual int					getCnt()override { return Products::getCnt(); }
	virtual string				getName() override { return Products::getName(); }
protected:
	string kind_;
};

class Breads :public Eating {
public:
	Breads				(int cnt, string name, int term, double cost, string kind) :Eating(cnt, name, term, cost), kind_(kind) {};
	virtual void				show()override { Eating::show(); cout << kind_ << endl; }
	virtual void				plusToCnt(int n)override { Products::plusToCnt(n); }
	virtual int					getCnt() override { return Products::getCnt(); }
	virtual string				getName() override{ return Products::getName(); }
protected:
	string kind_;
};

class Water :public Drinking {
public:
	Water				(int cnt, string name, int term, double cost, int V) :Drinking(cnt, name, term, cost), V_(V) {};
	virtual void				show() override { Drinking::show(); cout << V_ << endl; }
	virtual void				plusToCnt(int n) override { Products::plusToCnt(n); }
	virtual int					getCnt() override { return Products::getCnt(); }
	virtual string				getName() override { return Products::getName(); }
protected:
	int V_;
};

class Alcohol :public Drinking {
public:
	Alcohol				(int cnt, string name, int term, double cost, int V, int alcoPercent) :Drinking(cnt, name, term, cost), V_(V), alcoPercent_(alcoPercent){};
	virtual void				show() override { Drinking::show(); cout << V_ << alcoPercent_ << endl; }
	virtual void				plusToCnt(int n) override{ Products::plusToCnt(n); }
	virtual int					getCnt() override{ return Products::getCnt(); }
	virtual string				getName() override { return Products::getName(); }
protected:
	int V_, alcoPercent_;
};

