#pragma once
#pragma once
#include <string>

using namespace std;

class Review
{
public:
	string user;
	float score;
	int likes;
	int dislikes;
	string date;
	string comment;

	bool hasLiked = false;
	bool hasDislikes = false;

	Review* nextReview = nullptr;

	Review(string user, float score, int likes, int dislikes, string date, string comment) {
		this->user = user;
		this->score = score;
		this->likes = likes;
		this->dislikes = dislikes;
		this->date = date;
		this->comment = comment;
	}
};