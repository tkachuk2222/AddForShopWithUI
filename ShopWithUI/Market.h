#pragma once
#include<iomanip>
class Market
{
private:
	static Market		*market_;

	Market				() {}
	Market				(const Market&);
	Market&				operator=(Market&);

	
	Storage				st_;
	List<Cass*>			cassInStore_;
	vector<double>		cardID_;

public:
	friend Storage;
	friend Cass;
	friend Products;

	bool				isExistDiscount(double);
	void				addDiscountCard(double);

	void				addWorker(string name);

	void				addCassInStore(int num);

	double				getTotalPriceOfPurchase(int,int, bool, float);
	void				sellProd(int num, int cnt, int numCas, bool discount, float percent);
	void				addProdToStor(int num);
	void				showProdInMarket();
	void				showCashInCass();
	void				cashInCassToZero(int);
	void				delProduct(int num) { st_.delProd(num); }
	int					getCntOfCashRegister() { return cassInStore_.size(); }
	bool				isEmpty() { if (cassInStore_.isEmpty())return true; return false; };
	static Market *		getMarket() {
		if (!market_)
			market_ = new Market();
		return market_;
	}
	

};
Market* Market::market_;

void Market::addCassInStore(int num) {
	for (auto i = 0; i < num; i++)
		cassInStore_.addToBegin(new Cass);
}

void Market::showProdInMarket() {

	//cout << std::setw(20) << left << "Count" << std::setw(20) << left << "Product" << std::setw(20) << left << "Exp.date" << std::setw(20) << left << "Price" << endl;;
	printf("Count\t","Product\t", "Exp.date\t", "Price\n", 4, 4);
	//printf("Count,4.0f,Product,4.0f,Exp.date,4.0f,Price\n");
	cout << "Count\tProduct\tExp.date\tPrice\n";
	st_.showProd();
}

void Market::sellProd(int num, int cnt, int numCas, bool discount, float percent) {
	numCas--;
	try {
		if (!discount) {
			st_.sellProd(num, cnt);
			cassInStore_[numCas]->sellProd(st_.getStor(num)->getPrice(), cnt);//гроші в касу
		}
		else {
			st_.sellProd(num, cnt);
			double totalCash = st_.getStor(num)->getPrice() - (st_.getStor(num)->getPrice() * (percent / 100));
			cassInStore_[numCas]->sellProd(totalCash, cnt);
		}
	}				
	catch(const char*ex){
		cout << ex << endl;
	}
}

void Market::addProdToStor(int num) {
	system("cls");
	cout << "How much?" << endl;
	int cnt;
	cin >> cnt;
	if (num == 1) {
		st_.addProd(new Breads(cnt, "Some eating", 180, 5.5, "bulka"));
	}
	else if (num == 2) {
		st_.addProd(new Water(cnt, "CocaCola", 365, 20, 2.5));
	}
	else if (num == 3) {
		st_.addProd(new Alcohol(cnt, "Finlandia", 365, 100, 1, 40));
	}
	else if (num == 4) {
		st_.addProd(new Cookies(cnt, "Small cookies", 365, 4.34, "sm.cookies"));
	}
	else if (num == 5) {
		st_.addProd(new Cookies(cnt, "Big cookies", 90, 8.8, "big.cookies"));
	}
	else if (num == 6) {
		st_.addProd(new Alcohol(cnt, "Dark Beer", 90, 10.1, 0.5, 6.5));
	}
	else if (num == 7) {
		st_.addProd(new Eating(cnt, "Rice", 730, 2.29));
	}
	else if (num == 8) {
		st_.addProd(new Eating(cnt, "Buckwheat", 730, 2.29));
	}
}

void Market::showCashInCass() {
	for (int i = 0; i < cassInStore_.size(); i++)
	{
		cout << "cass №" << i - 1 << " " << cassInStore_[i]->cashInCass() << "$" << endl;
	}
}

void Market::cashInCassToZero(int numCass) {
	numCass--;
	cassInStore_[numCass]->setCash(0);
}

void Market::addWorker(string name) {

}

void Market::addDiscountCard(double ID) {
	//cardID_.addToBegin(ID);
	cardID_.push_back(ID);
}

bool Market::isExistDiscount(double cdID) {
	if(cardID_.empty())
		return false;
	for (int i = 0; i < cardID_.size(); i++)
	{
		if(cardID_[i] == cdID)
			return true;
	}
	return false;
	/*if (cardID_.isEmpty())
		return false;
	for (int i = 0; i < cardID_.size(); i++)
	{
		if (cardID_.getPosition(i) == cdID)
	}
	return false;*/
}

double Market::getTotalPriceOfPurchase(int position, int cnt, bool discount, float percent) {
	if(discount)
		return{ (st_.getStor(position)->getPrice() - (st_.getStor(position)->getPrice() * (percent / 100))) * cnt };
	return{ st_.getStor(position)->getPrice() * cnt };
}
