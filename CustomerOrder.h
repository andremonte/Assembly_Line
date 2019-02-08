//***********************************************************
// OOP345 Milestone 3:                      CustomerOrder.h /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     - Date: Ago 12, 2018   //
/////////////////////////////////////////////////////////////
//**********************************************************/
#pragma once
#include <iostream>
#include <string>
#ifndef CUSTOMER_ORDER_H_
#define CUSTOMER_ORDER_H_
class Item;

struct ItemInfo
{
	std::string ItemName;
	unsigned int SerialNumber;
	bool FillState; //means if I have or not this item in my warehouse

	ItemInfo(std::string src) : ItemName(src), SerialNumber(0), FillState(false) {};
};

class CustomerOrder
{
	std::string Name;
	std::string Product;
	unsigned int ItemCount;
	ItemInfo** ItemList;
	unsigned int field_width;

	void addItemList(std::string);
	void limparDados();

public:
	CustomerOrder();
	CustomerOrder(std::string&);
	~CustomerOrder();

	//Object is not allowed to be copied
	CustomerOrder(CustomerOrder&) { throw "ERROR:  Copy is not allows";  };			//should throw an exception if called
	CustomerOrder& operator=(CustomerOrder&) = delete;

	//Object move functionality
	CustomerOrder(CustomerOrder&&);
	CustomerOrder& operator=(CustomerOrder&&);

	bool getOrderFillState();								//Returns true if order completely filled, false otherwise
	bool getItemFillState(std::string);						//Returns true if the given item has been filled
	void fillItem(Item&, std::ostream&);					//Fills the customer order item if the inventory on Item is available

	void Display(std::ostream&);							//Displays the details of the CustomerOrder to the ostream object provided
};
#endif