#pragma once
#include <string>
#include "Review.h"

using namespace std;

class Product
{
public:
	string name;
	float price;
	float shipping;
	float stockCount;
	string description;
	Review* reviewHead;

	Product(string name, float price, float shipping, float stockCount, string description) {
		this->name = name;
		this->price = price;
		this->shipping = shipping;
		this->stockCount = stockCount;
		this->description = description;
	}

	void AddReview(Review* newReview) {

		if (reviewHead == nullptr)
			reviewHead = newReview;
		else {
			AddReview(newReview, reviewHead);
		}
	}
	void AddReview(Review* newReview, Review* node) {

		if (node->nextReview == nullptr)
			node->nextReview = newReview;
		else {
			AddReview(newReview, node->nextReview);
		}
	}

	Review* GetReview(int num) {
		return nullptr;
	}
};