// Lab_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bread.h"
#include "CupCake.h"
#include "LayerCake.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;

float CalculateTotal(BakedGood* item, int quantity)
{
	float itemsTotal = 0.0;

	if (item->GetType() == "Bread")
	{
		for (int i = 0; i < quantity; i++)
		{
			float discountedPrice = item->GetDiscountedPrice(i + 1);
			itemsTotal += discountedPrice;
		}
	}
	else //Both Cupcake and Layer-cake will enter here
	{
		float discountedPrice = item->GetDiscountedPrice(quantity);

		for (int i = 0; i < quantity; i++)
		{
			itemsTotal += discountedPrice;
		}

	}
	
	return itemsTotal;
}

void AddOrIncrementItem(BakedGood* item, vector<BakedGood*> &uniqueGoods, vector<int> &itemQuantites)
{
	bool isUnique = true;

	if (uniqueGoods.size() > 0)
	{
		for (int i = 0; i < uniqueGoods.size(); i++)
		{
			if (item->ToString() == uniqueGoods.at(i)->ToString()) //if item is already on the list, increment count by 1
			{
				isUnique = false;
				itemQuantites.at(i) += 1;
			}
		}
	}

	if (isUnique)
	{
		uniqueGoods.push_back(item);
		itemQuantites.push_back(1);
	}
}

void PrintInvoice(vector<BakedGood*> &bakedGoods)
{
	vector<BakedGood*> uniqueGoods;
	vector<int> itemQuantites;
	float totalCost = 0.0;
	int totalQuantity = bakedGoods.size();

	for (int i = 0; i < bakedGoods.size(); i++)
	{
		AddOrIncrementItem(bakedGoods.at(i), uniqueGoods, itemQuantites);
	}

	cout << "Invoice:" << endl;

	//for formatting invoice properly into aligned columns
	int goodsColumnSize = 75;
	int quantityColumnSize = 9;
	int totalsColumnSize = 9;

	// "left"/"right" aligns text in column. "setw()" sets column width.
	cout << left << setw(goodsColumnSize) << "Baked Good";
	cout << right << setw(quantityColumnSize) << "Quantity";
	cout << right << setw(totalsColumnSize) << "Total" << endl;

	float itemsTotal;
	ostringstream itemsCostAsString;
	
	for (int j = 0; j < uniqueGoods.size(); j++)
	{
		itemsTotal = CalculateTotal(uniqueGoods.at(j), itemQuantites.at(j));
		itemsCostAsString << setprecision(2) << fixed << itemsTotal; //formats price to two decimal places
		totalCost += itemsTotal;

		cout << left << setw(goodsColumnSize) << uniqueGoods.at(j)->ToString();
		cout << right << setw(quantityColumnSize) << itemQuantites.at(j);
		cout << right << setw(totalsColumnSize) << itemsCostAsString.str();
		itemsCostAsString.str(""); //clears itemsCostAsString for next item
		cout << endl;
	}

	cout << left << setw(goodsColumnSize) << "Totals";
	cout << right << setw(quantityColumnSize) << totalQuantity;
	cout << right << setw(totalsColumnSize) << setprecision(2) << fixed << totalCost << endl;
}

void CreateOrder(string order, vector<BakedGood*> &bakedGoods)
{
	//splits up order string for parsing
	istringstream orderStream(order);
	vector<string> splitOrder((istream_iterator<string>(orderStream)), istream_iterator<string>());
	string goodType = splitOrder.at(0);
	int numOfGoods = stoi(splitOrder.at(splitOrder.size() - 1)); //gets number of goods at end of string

	for (int i = 0; i < numOfGoods; i++)
	{
		if (goodType == "Bread")
		{
			string variety = splitOrder.at(1);
			bakedGoods.push_back(new Bread(variety));
		}
		else if (goodType == "Cupcake")
		{
			string flavor = splitOrder.at(1);
			string frostingFlavor = splitOrder.at(2);
			string sprinkleColor = splitOrder.at(3);
			bakedGoods.push_back(new CupCake(flavor, frostingFlavor, sprinkleColor));
		}
		else if (goodType == "Layer-cake")
		{
			string flavor = splitOrder.at(1);
			string frostingFlavor = splitOrder.at(2);
			int numLayers = stoi(splitOrder.at(3));
			bakedGoods.push_back(new LayerCake(flavor, frostingFlavor, numLayers));
		}
	}
}

int main()
{
	cout << "**Bread and Cakes Bakery**" << endl << endl;

	vector<BakedGood*> bakedGoods;
	string order;
	cout << "Enter sub-order (enter \"done\" to finish)" << endl;

	do
	{
		cout << "Sub-order: ";
		getline(cin, order);

		if (order != "done")
		{
			CreateOrder(order, bakedGoods);
		}
	} while (order != "done");

	cout << endl << "Order Confiramtions:" << endl;
	for (int i = 0; i < bakedGoods.size(); i++)
		cout << bakedGoods.at(i)->ToString() << endl;

	cout << endl;
	PrintInvoice(bakedGoods);
	cout << "Good Bye" << endl;

	system("pause");
    return 0;
}

