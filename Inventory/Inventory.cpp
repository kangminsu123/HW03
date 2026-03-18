#include <string>
#include <iostream>
#include<algorithm>

// Item class 정의
class Item
{
public:
	Item(const std::string& name = "", int price = 0);
	const std::string& GetName() const;
	int GetPrice() const;
	void Clear()
	{
		name_ = "";
		price_ = 0;
	}


private:
	std::string name_;
	int price_;
};

Item::Item(const std::string& name, int price) : name_(name), price_(price) {}


const std::string& Item:: GetName() const
{
	return name_;
}

int Item::GetPrice() const
{
	return price_;
}

bool compareItemsByPrice(const Item& a, const Item& b) {
	return a.GetPrice() < b.GetPrice();
}
// Inventory<T> class 정의
template<typename T>
class Inventory
{
public:
	Inventory(int capacity = 10) : capacity_(capacity), size_(0)
		{
		pItems_ = new T[capacity_];
		}
	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		std::cout << "인벤토리 복사 완료" << std::endl;
	}

	~Inventory() 
	{
		delete[] pItems_;
	}

	void AddItem(const T& item)
	{
		if (size_ >= capacity_)
		{
			std::cout << "Inventory is full. Cannot add more items." << std::endl;
			return;
		}
		pItems_[size_++] = item;
	}
	void RemoveLastItem()
	{
		if (size_ > 0)
		{
			pItems_[--size_].Clear();
		}
		else
		{
			std::cout << "Inventory is empty. No items to remove." << std::endl;
		}
	}// size_--을 활용하여 마지막 아이템을 Clear
	int GetSize() const 
	{
		return size_;
	}
	// size_
	int GetCapacity() const
	{
		return capacity_;
	}
	void PrintAllItems() const
	{
		for (int i = 0; i < size_; ++i)
		{
			std::cout << "Item Name: " << pItems_[i].GetName() << ", Price: " << pItems_[i].GetPrice() << std::endl;
		}
	}
	void SortItems()
	{
		std::sort(pItems_, pItems_ + size_, compareItemsByPrice);
	}

	void Resize(int newCapacity)
	{
		if (newCapacity <= capacity_)
		{
			std::cout << "업그레이드에 실패했습니다." << std::endl;
			return;
		}
		T* newItems = new T[newCapacity];
		for (int i = 0; i < size_; ++i)
		{
			newItems[i] = pItems_[i];
		}
		delete[] pItems_;
		pItems_ = newItems;
		capacity_ = newCapacity;
	}
private:
	T* pItems_;
	int capacity_;
	int size_;
};


	int main()
	{
		Inventory<Item>* itemInventory = new Inventory<Item>();
		for (int i = 0; i < 11; ++i)
		{
			itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
		}

		itemInventory->PrintAllItems();
		std::cout << "ItemCapacity : " << itemInventory->GetCapacity() << std::endl;

		itemInventory->Resize(25);
		for (int i = 0; i < 14; ++i)
		{
			itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
		}

		itemInventory->PrintAllItems();
		std::cout << "ItemCapacity : " << itemInventory->GetCapacity() << std::endl;

		itemInventory->SortItems();
		itemInventory->PrintAllItems();

		Inventory<Item>* itemInventory2 = new Inventory<Item>(*itemInventory);
		itemInventory2->PrintAllItems();

		delete itemInventory;
		delete itemInventory2;

		return 0;
	}