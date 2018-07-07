// Lab_10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bread.h"
#include "CupCake.h"
#include "LayerCake.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<BakedGood*> bakedGoods;
	bakedGoods.push_back(new Bread("Wheat"));
	bakedGoods.push_back(new CupCake("Funfetti", "lemon", "pink"));
	bakedGoods.push_back(new LayerCake("Chocolate", "vanilla", 2));

	for (int i = 0; i < bakedGoods.size(); i++)
	{
		cout << bakedGoods.at(i)->ToString() << endl;
	}

	system("pause");
    return 0;
}

