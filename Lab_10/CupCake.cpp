#include "stdafx.h"
#include "CupCake.h"

CupCake::CupCake(string flavor, string frosting, string sprinklesColor)
{
	this->flavor = flavor;
	this->frosting = frosting;
	this->sprinklesColor = sprinklesColor;
	price = 1.95;

	const float costOfCreamCheese = 0.20;
	if (frosting == "cream-cheese")
		price += costOfCreamCheese;

	goodType = "Cupcake";
}

CupCake::~CupCake()
{
}

string CupCake::ToString()
{
	return flavor + " cupcake with " + frosting + " frosting and " + sprinklesColor + " sprinkles " + BakedGood::ToString();
}
