#pragma once
using namespace std;


class Wokers
{
public:
	Wokers				(string name): name_(name) {};
	virtual void		showPerson() { cout << name_; };
private:
	string name_;
};

//void Cashiers::addCas(string name) {
//	cas_.addToBegin()
//}

class Cashiers :public Wokers {
public:
	Cashiers			(string name) : Wokers(name) {};
	virtual void		showPerson() override { Wokers::showPerson(); }
private:
};

class Admin :public Wokers {
public:
	Admin				(string name) :Wokers(name) {};
	virtual void		showPerson() override { Wokers::showPerson(); }
};

class Director :public Wokers {
public:
	Director			(string name) :Wokers(name) {};
	void				addCashier(string name);
	void				addAdmin(string name);
	virtual void		showPerson() override { Wokers::showPerson(); }
};

class Personal {
public:
	Personal			() {};
	friend Wokers;
	
private:
	List<Wokers*>emp_;
};

void Director::addCashier(string name) {

}