#pragma once
//#include <algorithm>

class Storage {
public:
	Storage				() { cout << "const storage" << endl; };
	friend Products;
	friend Cass;
//	friend Market;
	template<typename T>
	void				addProd(T p);

	void				showProd();
	void				sellProd(int num, int cnt);
	Products*			getStor(int num) { return{ stor_[num] }; }
	void				delProd(int num) { stor_.removeByPosition(num); }
protected:
	List<Products*>		stor_;
	
//	list<Products*>stor_;
};

void Storage::showProd() {
	for (int i = 0; i < stor_.size(); ++i)
	{
		Products*tmp = stor_[i];
		tmp->show();
		cout << endl;
	}
}

inline void Storage::sellProd(int num, int cnt)
{
	Products*tmp = stor_[num];
	if (tmp->getCnt() == 0) {
		throw "This product is already sold";
	}
	tmp->getProd(cnt);											//мінус кількість продуктів

}
template<typename T>
inline void Storage::addProd(T p) {
	if (!stor_.isEmpty()) {
		for (int i = 0; i < stor_.size(); i++)
		{
			Products*prod = p;
			Products*tmp = stor_[i];
			if (prod->getName() == tmp->getName()) {
				//if (typeid(*prod) == typeid(*tmp)) {
				tmp->plusToCnt(p->getCnt());
//				addCnt = true;
				return;
			}
		}
	}
	stor_.addToBegin(p);
}

//void Storage::showProd() {
//	for (int i = 0; i < stor_.size(); ++i)
//	{
//		List<Products*>tmp = stor_[i];
//		Products *prod = tmp.getData();
//		prod->show();
//		cout << endl;
//	}
//}
//
//inline void Storage::giveProd(int num, int cnt)
//{
//	List<Products*>tmp = stor_[num];
//
//	//tmp->getProd(cnt);
//}
