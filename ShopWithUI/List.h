#pragma once


template<typename T>
class List
{
public:
	List				() :list_(nullptr) {};//  створює пустий список
	List				(const List&ob); //
	List				(List&& ob); //?
	~List				();
	void				clear();
	void				show();
	void				addToBegin(T data);
	void				removeFromBegin();
	void				removeFromEnd();
	bool				remove(T num);
	bool				removeByPosition(int num);
	bool				isEmpty();
	T					getPosition(int);
	int					size() const;
	T&					operator[](int);
	T					getData();
	void				setData(int, T);
private:
	class Item
	{
	public:
		friend List;
		Item(T data = 0) :data_(data), pnext_(nullptr) {};
	private:
		T data_;
		Item*pnext_;
	};
	Item*list_;
};

template<typename T>
List<T>::List(const List<T>&ob) {
	Item*tmp = nullptr;
	Item*OBtmp = ob.list_;
	while (OBtmp != nullptr) {
		if (tmp != nullptr) {
			tmp->pnext_ = new Item;
			tmp = tmp->pnext_;
			tmp->data_ = OBtmp->data_;
			//		tmp->pnext_ = nullptr;
			OBtmp = OBtmp->pnext_;
		}
		else {
			tmp = new Item;
			list_ = tmp;
			tmp->data_ = OBtmp->data_;
			//		tmp->pnext_ = nullptr;
			OBtmp = OBtmp->pnext_;
		}
	}
	cout << "Constructor copy\n";

}

template<typename T>
List<T>::List(List<T>&& ob) {
	Item*tmp = nullptr;
	while (ob.list_ != nullptr) {
		if (tmp == nullptr) {
			tmp = new Item;
			list_ = tmp;
		}
		tmp->data_ = ob.list_->data_;
		tmp->pnext_ = nullptr;
		tmp->pnext_ = new Item;
		ob.list_->data_ = 0;
		ob.list_ = nullptr;
		ob.list_ = ob.list_->pnext_;
	}
	ob.list_ = nullptr;
	cout << "Constructor move\n";
}

template<typename T>
List<T>::~List()
{
	cout << "destructor\n";
	clear();
}

template<typename T>
void List<T>::clear() {
	if (!list_)
		return;
	else {
		if (!list_->pnext_) {
			delete list_;
			return;
		}
		else {
			Item*nextElem = list_->pnext_;
			while (list_) {
				delete list_;
				list_ = nextElem;
				if (!list_)
					return;
				nextElem = nextElem->pnext_;

			}
		}
	}
}

template<typename T>
void List<T>::show() {
	if (list_ != nullptr) {
		Item *tmp = list_;
		while (tmp != nullptr) {
			cout << *tmp->data_ << "\t";
			tmp = tmp->pnext_;
		}
	}
	else
		cout << "List is empty\n";
	cout << endl;
}

template<typename T>
void List<T>::addToBegin(T data)
{
	Item*it = new Item(data);
	if (list_ != nullptr)
		it->pnext_ = list_;
	list_ = it;
}

template<typename T>
void List<T>::removeFromBegin() {
	Item*tmp = list_;
	list_ = list_->pnext_;
	delete tmp;
	return;
}

template<typename T>
void List<T>::removeFromEnd() {
	if (list_)
		if (list_->pnext_) {
			Item*tmp = list_;
			while (tmp->pnext_->pnext_)
				tmp = tmp->pnext_;
			delete tmp->pnext_;
			tmp->pnext_ = nullptr;
		}
		else {
			delete list_;
			list_ = nullptr;
		}
}

template<typename T>
bool List<T>::removeByPosition(int num) {
	if (!list_)
		return false;
	Item*prev_tmp = list_;
	Item*tmp = prev_tmp;
	if (num == 1) {
		removeFromBegin();
		return true;
	}
	//else if()
	else {
		int count = 1;
		while (tmp->pnext_) {
			if (count == num)
				break;
			prev_tmp = tmp;
			tmp = tmp->pnext_;
			count++;
		}
		if (!tmp) return false;
		else {
			if (!tmp->pnext_) {
				removeFromEnd();
				return true;
			}
			else {
				prev_tmp->pnext_ = tmp->pnext_->pnext_;
				delete tmp;
				return true;
			}
		}
	}
}

template<typename T>
bool List<T>::remove(T num) {
	if (!list_)
		return false;
	Item*prev_tmp = list_;
	Item*tmp = prev_tmp;
	if (list_->data_ == num) {
		removeFromBegin(num);
		return true;
	}
	//else if()
	else {
		while (tmp->pnext_) {
			if (tmp->data_ == num)
				break;
			prev_tmp = tmp;
			tmp = tmp->pnext_;
		}
		if (!tmp) return false;
		else {
			if (!tmp->pnext_) {
				removeFromEnd();
				return true;
			}
			else {
				prev_tmp->pnext_ = tmp->pnext_->pnext_;
				delete tmp;
				return true;
			}
		}
	}
}

template<typename T>
bool List<T>::isEmpty() {
	if (!list_)
		return true;
	return false;
}

template<typename T>
inline T List<T>::getPosition(int num)
{
	if (list_) {
		Item*tmp = list_;
		int cnt = 0;
		while (tmp->pnext_) {
			if (cnt == num)
				return tmp->data;
			cnt++;
		}
		return 0;
	}
	else
		return 0;
//	return List();
}

template<typename T>
int List<T>::size() const {
	if (!list_) {
		return 0;
	}
	else {
		Item*tmp = list_;
		unsigned long count = 0;
		while (tmp) {
			tmp = tmp->pnext_;
			count++;
		}
		return count;

	}
}




//template<typename T>
//inline T & List<T>::operator[](int)
//{
//	// TODO: insert return statement here
//}

template<typename T>
T& List<T>::operator[](int index)
{
	

		int count = 0;
		Item*tmp = list_;
		while (tmp) {
			if (count == index)
				return tmp->data_;
			tmp = tmp->pnext_;
			count++;
		}

}

template<typename T>
inline T List<T>::getData()
{
	return list_->data_;
}

template<typename T>
inline void List<T>::setData(int num, T data)
{
	if (list_) {
		Item*tmp = list_;
		int cnt = 0;
		while (tmp) {
			if (cnt == num) {
				tmp->data_ = data;
				return;
			}
			cnt++;
			tmp = tmp->pnext_;
		}
	}
}
