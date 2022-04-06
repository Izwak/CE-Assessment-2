#include <iostream>
#include <string>
#include <Windows.h>
#include "Product.h"

using namespace std;

enum Colour {
	DARKBLUE = 0x00001,
	DARKGREEN = 0x0002,
	DARKCYAN = 0x0003,
	DARKRED = 0x0004,
	PURPLE = 0x0005,
	PUKE = 0x0006,
	GRAY = 0x00007,
	DARKGRAY = 0x0008,
	BLUE = 0x0009,
	GREEN = 0x000a,
	CYAN = 0x000b,
	RED = 0x000c,
	MAGENTA = 0x0000d,
	YELLOW = 0x000e,
	WHITE = 0x000f,
};

enum Page {
	SIGNIN,
	LOGIN,
	PRODUCT,
	REVIEW,
	CART,
	CHECKOUT,
	SHIPPING,
};

enum Interactions {
	DEFAULT,
	QUANTITY,
	CONTINUE,
	BACKTOPRODUCT,
	LIKE,
	DISLIKE,
};

Product product(
	"Boot", // Name
	120, // Cost
	20, // Shipping
	3, // Stock Count
	"This is a boot it do boot things it is red the brand is the 1 that is the good 1" // Description
);

string username;
string address = "Your Mum's Basement";
string cardNum = "**** **** **** *321";
string testNum;
int quantityInCart;

bool isDescriptionShown = false;
bool isCallingSupport = false;
bool isOutcomeShown = false;
bool isInteractionShown = true;
bool isLooping = true;

Colour defaultColour;
Page savedPage;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// Set Colour Sets the colour from now on to be "colour" as well as the default colour
void SetColour(Colour colour) {

	SetConsoleTextAttribute(h, colour);
	defaultColour = colour;
}

// Coloured Text will change the text colour to "colour" but will then change the colour back to what it was before
void ColouredText(string text, Colour colour) {
	SetConsoleTextAttribute(h, colour);
	cout << text;
	SetConsoleTextAttribute(h, defaultColour);
}

void FixedGetline(string& text) {
	string temp = "";
	cin >> temp;
	getline(cin, text);
	text = temp + text;
}

bool isCharNum(char c) {

	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
		return true;
	}
	return false;
}

Review* LeaveReview() {

	Review* newReview = new Review(username, 0, 0, 0, "Now", "");

	while (newReview->score == 0 || newReview->comment == "") {
		system("CLS");

		ColouredText("/////Webpage////////////////////////\n\n", DARKGREEN);
		cout << "Welcome to OneStop ";
		username != "" ? ColouredText(username, GREEN) : ColouredText("Guest", RED);

		cout << "\n\nUser: ";
		ColouredText(newReview->user, GREEN);
		cout << ", Score: " << newReview->score << ", Date: " << newReview->date << endl;
		cout << "\tComment: ";
		ColouredText("\t" + newReview->comment, DARKGRAY);

		ColouredText("\n\n/////Interactions///////////////////\n", DARKGREEN);

		if (newReview->score == 0) {
			cout << "Score \"" << product.name << "\" (From 1-5): ";

			float choice;
			cin >> choice;

			if (choice > 5 || choice < 1) {
				cout << "\nScore outside acceptable range Try again\n";
				system("pause");
			}
			else {
				newReview->score = choice;
			}

		}
		else if (newReview->comment == "") {

			cout << "Comment: ";

			getline(cin, newReview->comment);
		}

	}
	return newReview;
}

void LoadWebPage(Page& page) {

	ColouredText("/////Webpage////////////////////////\n\n", DARKGREEN);
	SetColour(GRAY);

	cout << "Welcome to OneStop ";
	username != "" ? ColouredText(username, GREEN) : ColouredText("Guest", RED);

	if (page == SIGNIN) {
		cout << "\n\nSign in Page\n\n";
	}
	else if (page == PRODUCT) {

		cout << "\n\nProduct: " + product.name << endl;
		cout << "Price: $" << product.price << endl;
		cout << "Shipping: +$" << product.shipping << endl;
		cout << "Stock: " << product.stockCount << endl;

		cout << "\nDescription " << (!isDescriptionShown ? "^\n" : "v\n");
		if (isDescriptionShown)
			ColouredText(product.description + "\n", DARKGRAY);

		cout << "\nReviews ^ \n\n";

		cout << (quantityInCart == 0 ? "[Add to Cart]\n\n" : "[Show in Cart]\n\n");

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "Thank you for calling customer support. At OneStop we what to make sure that the product you get, \n";

			cout << "is the one that you want. To get a better visual of the product you can ";
			ColouredText("[Inspect the Product]", WHITE);

			cout << ". \nFor more Info about the product you can ";
			ColouredText("[Look at the Description]", WHITE);
			cout << " to find the specs. Still not sure \nif you'll like it you can ";


			ColouredText("[Look at the Reviews]", WHITE);
			cout << ". Once you're confident that you're happy with your find \n";

			ColouredText("[Add to Cart]", WHITE);
			cout << " then continue browsing. \n\n";

			SetColour(GRAY);
		}
	}
	else if (page == REVIEW) {

		Review* review = product.reviewHead;

		int num = 1;

		cout << "\n\nReviews v\n\n";

		// Load in all the Reviews
		while (review != nullptr)
		{

			ColouredText(to_string(num) + ") ", PURPLE);
			cout << "User: ";
			ColouredText(review->user, GREEN);
			cout << ", Score: " << review->score << ", Date: " << review->date << endl;
			cout << "\tComment: \n";
			ColouredText("\t" + review->comment, DARKGRAY);
			cout << "\n\tLikes: ";
			ColouredText(to_string(review->likes + ((review->hasLiked) ? 1 : 0)), ((review->hasLiked) ? DARKGREEN : GRAY));
			cout << ", Dislikes: ";
			ColouredText(to_string(review->dislikes + ((review->hasDisliked) ? 1 : 0)), ((review->hasDisliked) ? DARKRED : GRAY));
			cout << endl << endl;

			num++;
			review = review->nextReview;
		}

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "Looking through the reviews of happy customers can help you decided if you're ready to buy our products. \nYou can ";
			ColouredText("[Like a Review]", WHITE);
			cout << " or ";
			ColouredText("[Dislike a Review]", WHITE);
			cout << " to give feedback on whether you thought their reviews where helpful \nto you or not or even ";
			ColouredText("[Leave a Review]", WHITE);
			cout << " yourself. Once you're ready ";
			ColouredText("[Go Back]", WHITE);
			cout << " to continue with your browsing." << endl << endl;

			SetColour(GRAY);
		}
	}
	else if (page == CART) {
		cout << "'s Cart \nProducts:\n\n";
		ColouredText("1) ", PURPLE);
		cout << product.name << ", Quantity: " << quantityInCart << ", Price: $" << product.price << ", Shipping: $" << product.shipping << endl << endl;

		cout << "   Price: \t$" << product.price << endl;
		cout << "   Quantity: \tx" << quantityInCart << endl;
		cout << "   Shipping: \t+$" << product.shipping << endl;
		cout << "   __________________\n";
		cout << "   Total: \t$" << product.price * quantityInCart + product.shipping << endl << endl;

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "Welcome to the cart! If you need to you can always go "; 
			ColouredText("[Back to Product]", WHITE);
			cout << " for more info. \nOnce you're happy ";
			ColouredText("[Proceed to Checkout]", WHITE);
			cout << " to finalise the purchase, but you still can \n";
			ColouredText("[Adjust Quantity]", WHITE);
			cout << " and ";
			ColouredText("[Change Shipping]", WHITE);
			cout << " if you would like them to change.\n\n";
		}

		SetColour(GRAY);
	}
	else if (page == CHECKOUT) {

		ColouredText("\n\nThank you for shoping with us at OneStop \nPlease confirm your information is correct before finalising your order\n\n", DARKGRAY);
		ColouredText("User: ", WHITE);
		ColouredText(username, GREEN);
		cout << "\n   Product(s): \t" << product.name << " (x" << quantityInCart << ")" << endl;
		cout << "   Total Cost: \t$" << product.price * quantityInCart + product.shipping << " (Shipping Included)\n";

		cout << "   Shipping: \t$" << product.shipping;
		if (product.shipping == 20)
			cout << ", Default Delivery \n";
		else if (product.shipping == 40)
			cout << ", Speedy Delivery \n";
		else if (product.shipping == 60)
			cout << ", Premium Delivery \n";
		else
			cout << ", Instant Delivery \n";

		cout << "   Address: \t" << address << endl;

		if (product.shipping == 20)
			cout << "   ETA: \t20-25 Buisness Days\n"; 
		else if (product.shipping == 40)
			cout << "   ETA: \t10-15 Buisness Days\n";
		else if (product.shipping == 60)
			cout << "   ETA: \t3-5 Buisness Days\n";
		else
			cout << "   ETA: \t0 Buisness Days u already have it lol\n";

		cout << "   Card Num: \t" << cardNum << "\n\n";

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "Finally we can ";
			ColouredText("[Confirm Purchase]", WHITE);
			cout << " and we're done, if you don’t need to ";
			ColouredText("[Head Back to Cart]", WHITE);
			cout << " first. \nAnd remember you can ";
			ColouredText("[Change Shipping Address]", WHITE);
			cout << " and ";
			ColouredText("[Change Card Number]", WHITE);
			cout << " if they have changed \nsince last time (You can put spaces if necessary).\n\n";

			SetColour(GRAY);
		}
	}
	else if (page == LOGIN) {
		cout << "\n\nLog in Page\n   Username: " << username << "\n   Password: " << (username != "" ? "*******" : "") << endl;
	}
	else if (page == SHIPPING) {
		
		cout << "\n\nShipping options";

		ColouredText("\n\n1) ", PURPLE);
		cout << "Standard Delivery: \n\tCost: $20 \n\tETA: 20-25 Business Days\n\n";
		ColouredText("2) ", PURPLE);
		cout << "Speedy Delivery: \n\tCost: $40 \n\tETA: 10-15 Business Days\n\n";
		ColouredText("3) ", PURPLE);
		cout << "Premium Delivery: \n\tCost: $60 \n\tETA: 3-5 Business Days\n\n";

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "There are 3 delivery options with pricing increasing in return for faster deliveries. \n\n";

			SetColour(GRAY);
		}
	}
	else {
		cout << "Oops there was a dun goof ur stuck here my b" << endl;
	}
}

void LoadOutcome(Page& page, Interactions& interaction, long long& choice) {

	if (!isOutcomeShown) {
		isInteractionShown = true;
		return;
	}

	ColouredText("/////Outcome////////////////////////\n", DARKGREEN);
	SetColour(GRAY);

	if (page == SIGNIN) {
		switch (choice) {
		case 1:
			page = LOGIN;
			savedPage = PRODUCT;
			break;
		case 2:
			page = PRODUCT;
			break;
		default:
			cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
			cout << "Please put in a valid choice\n";
			system("pause");
			break;
		}
	}
	else if (page == PRODUCT) {
		if (interaction == DEFAULT) {
			switch (choice)
			{
			case 1:
				cout << "You inspected the product \nHmm... yes from these Images alone they appear to be of high quality\n";
				system("pause");
				break;

			case 2:
				cout << (isDescriptionShown ? "You close" : "You open") << " the description\n";
				isDescriptionShown = !isDescriptionShown;
				system("pause");
				break;

			case 3:
				cout << "You opened up the reviews\n";
				page = REVIEW;
				system("pause");
				break;

			case 4:
				if (quantityInCart == 0) {
					cout << "Adding " << product.name << " to the cart\n\n";
					interaction = QUANTITY;
					isInteractionShown = true;
				}
				else {

					cout << "You went to your cart\n";
					page = CART;
					system("pause");
				}
				break;

			case 5:
				cout << (isCallingSupport ? "You have ended" : "You have called") << " the customer support\n";
				isCallingSupport = !isCallingSupport;
				system("pause");
				break;

			default:
				cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
				cout << "Please put in a valid choice\n";
				system("pause");
				break;
			}
		}
		// Works out if theres enough in stock
		else if (interaction == QUANTITY) {
			if (choice < 0) {

				cout << "Sorry you can't buy negative of a product" << endl;
			}
			else if (choice == 0) {

				cout << "You decided to not get any " << product.name << "s \n";
				interaction = DEFAULT;
			}
			else if (choice > product.stockCount) {
				cout << "Sorry there aren't enough of " << product.name << " in stock as there's only " << product.stockCount << " left\n";
			}
			else {
				cout << choice << " " << product.name << " was added to your cart " << endl;
				quantityInCart = choice;
				interaction = BACKTOPRODUCT;
			}
			system("pause");
		}
		else if (interaction == CONTINUE) {
			cout << "Successfully added " << choice << " to your cart\n\n";

			//isInteractionShown = true;
			system("pause");
		}
		else if (interaction == BACKTOPRODUCT) {

			switch (choice)
			{
			case 1:
				cout << "Back to Product\n\n";
				page = PRODUCT;
				interaction = DEFAULT;
				isInteractionShown = true;
				break;
			case 2:
				cout << "Move to Cart\n\n";
				page = CART;
				interaction = DEFAULT;
				//isInteractionShown = true;
				break;
			default:
				cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
				cout << "Please put in a valid choice\n";

				system("pause");
				break;
			}

		}
	}
	else if (page == REVIEW) {

		if (interaction == DEFAULT) {


			if (username == "") {
				page = LOGIN;
				savedPage = REVIEW;
			}

			switch (choice)
			{
			case 1:
				if (username == "") {
					page = LOGIN;
					savedPage = REVIEW;
					cout << "Before you can complete this action you must be signed in\n";
					system("pause");
				}
				else {
					cout << "Leave Review\n";
					product.AddReview(LeaveReview());
				}
				break;
			case 2:
				if (username == "") {
					page = LOGIN;
					savedPage = REVIEW;
					cout << "Before you can complete this action you must be signed in\n";
					system("pause");
				}
				else {
					interaction = LIKE;
				}
				break;
			case 3:
				if (username == "") {
					page = LOGIN;
					savedPage = REVIEW;
					cout << "Before you can complete this action you must be signed in\n";
				}
				else {
					interaction = DISLIKE;
				}
				break;

			case 4:
				cout << "You head back to the product page\n";
				page = PRODUCT;
				system("pause");
				break;

			case 5:
				cout << (isCallingSupport ? "You have ended" : "You have called") << " the customer support\n";
				isCallingSupport = !isCallingSupport;
				system("pause");
				break;

			default:
				cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
				cout << "Please put in a valid choice\n";
				system("pause");
				break;
			}
		}
		else if (interaction == LIKE) {

			Review* review = product.GetReviewAt(choice);

			if (product.ReviewCount() == 0) {
				cout << "Apparently theres no reviews to like just your luck\n";
			}
			else if (choice > product.ReviewCount() || choice < 1) {
				cout << "Out of scope pick a number on the list\n";
			}
			else if (review != nullptr)	{

				if (username == review->user) {
					if (review->hasLiked)
						cout << "You have unliked your own review... It wasn't that bad\n";
					else
						cout << "You have liked your own review... Self centered much\n";
				}
				else {
					if (review->hasLiked) {

						cout << "You have unliked ";
					}
					else
						cout << "You have liked ";

					ColouredText(review->user, GREEN);
					cout << "'s review\n";
				}

				review->hasLiked = !review->hasLiked;
				review->hasDisliked = false;
				interaction = DEFAULT;
			}		
			else if (review == nullptr) {
				ColouredText("NULL" + to_string(choice), PUKE);
			}

			system("pause");
		}
		else if (interaction == DISLIKE) {

			Review* review = product.GetReviewAt(choice);

			if (product.ReviewCount() == 0) {
				cout << "Apparently theres no reviews to like just your luck\n";
			}
			else if (choice > product.ReviewCount() || choice < 1) {
				cout << "Out of scope pick a number on the list\n";
			}
			else if (review != nullptr) {

				if (username == review->user) {
					if (review->hasDisliked)
						cout << "You have undisliked your own review... That was a mouth full\n";
					else
						cout << "You have disliked your own review... At least you know your place\n";
				}
				else {
					if (review->hasDisliked) {

						cout << "You removed your dislike ";
					}
					else
						cout << "You have disliked ";

					ColouredText(review->user, GREEN);
					cout << "'s review\n";
				}

				review->hasDisliked = !review->hasDisliked;
				review->hasLiked = false;
				interaction = DEFAULT;
			}
			else if (review == nullptr) {
				ColouredText("NULL" + to_string(choice), PUKE);
			}

			system("pause");
		}
	}
	else if (page == CART) {
		if (interaction == DEFAULT) {
			switch (choice)
			{
			case 1:
				cout << "You went back to Product\n";
				page = PRODUCT;
				system("pause");
				break;
			case 2:
				if (username != "") {
					cout << "You headed to the checkout\n";
					page = CHECKOUT;
				}
				else {
					cout << "Before you can Checkout you need to be signed in\n";
					page = LOGIN;
					savedPage = CHECKOUT;
				}
				system("pause");
				break;
			case 3:
				cout << "You Attempt to change the Quantity\n";
				interaction = QUANTITY;
				isInteractionShown = true;
				break;
			case 4:
				page = SHIPPING;
				break;
			case 5:
				cout << (isCallingSupport ? "You have ended" : "You have called") << " the customer support\n";
				isCallingSupport = !isCallingSupport;
				system("pause");
				break;
			default:
				cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
				cout << "Please put in a valid choice\n";
				system("pause");
				break;
			}
		}
		else if (interaction == QUANTITY) {
			if (choice > product.stockCount) {
				cout << "Sorry there aren't enough of " << product.name << " in stock as there's only " << product.stockCount << " left\n";
			}
			else if (choice < 0) {
				cout << "Sorry you can't buy negative of a product\n";
			}
			else if (choice == 0) {
				cout << "You remove " << product.name << " from your cart\n";
				cout << "I hope your happy with yourself\n";
				
				quantityInCart = choice;
				page = PRODUCT;
				interaction = DEFAULT;
			}
			else if (choice == quantityInCart) {
				cout << "Thats just what it was before u ok there bud???\n";
				interaction = DEFAULT;
			}
			else {
				cout << "The quantity of " << product.name << " has been updated to " << choice << endl;
				quantityInCart = choice;
				interaction = DEFAULT;
			}
			system("pause");
		}
	}
	else if (page == CHECKOUT) {
		if (interaction == DEFAULT) {

			switch (choice) {
			case 1:
				cout << "Confirm Purchase \nCongratulations on your purchase, come back soon!\n";
				interaction = CONTINUE;
				system("pause");
				return;
			case 2:
				cout << " Head Back to Cart\n";
				page = CART;
				system("pause");
				break;
			case 3:
				cout << "Addresss : ";
				FixedGetline(address);
				break;
			case 4:
				interaction = QUANTITY;
				break;
			case 5:
				cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";
				isCallingSupport = !isCallingSupport;
				system("pause");
				break;
			default:
				cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
				cout << "Please put in a valid choice\n";
				system("pause");
				break;
			}
		}
		else if (interaction == QUANTITY) {

			int length = 0;
			string censoredCardNum;

			//char* array = new char[testNum.length()];

			for (int i = 0; i < testNum.length(); i++) {
				

				if (!isCharNum(testNum[i]) && testNum[i] != ' ') {

					cout << "Cant include letters or symbols\n";
					return;
				}
				else if (testNum[i] != ' ') {
					length++;
					if (i < testNum.length() - 3)
						censoredCardNum += "*";
					else
						censoredCardNum += testNum[i];
				}
				else if (testNum[i] == ' ') {
					censoredCardNum += " ";
				}
			}

			if (length > 20) {
				cout << "Number too Long\n";
				system("pause");
			}
			else if (length < 12) {

				cout << "Number too Short\n";
				system("pause");
			}
			else {

				//testNum = array[length - 3] + array[length - 2] + array[length - 1];

				cout << " Changed Card Num to: " << testNum << endl;
				cardNum = censoredCardNum;
				interaction = DEFAULT;
				system("pause");
			}

		}
	}
	else if (page == LOGIN) {
		cout << "Thank you for signing in :D \nWe will now return to our reguarly scheduled program\n";
		page = savedPage;
		system("pause");
	}
	else if (page == SHIPPING) {

		switch (choice)
		{
		case 1:
			cout << "You choose the Standard Delivery\n";
			product.shipping = 20;
			page = CART;
			break;
		case 2:
			cout << "You choose the Speedy Delivery\n";
			product.shipping = 40;
			page = CART;
			break;
		case 3:
			cout << "You choose the Premium Delivery\n";
			product.shipping = 60;
			page = CART;
			break;
		default:
			cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
			cout << "Please put in a valid choice\n";
			break;
		}
		system("pause");
	}
}

void LoadInteractions(Page& page, Interactions& interaction, long long& choice) {

	if (!isInteractionShown) {

		isOutcomeShown = false;
		return;
	}
	else {

		isOutcomeShown = true;
		isInteractionShown = false;
	}

	ColouredText("/////Interactions///////////////////\n", DARKGREEN);
	SetColour(WHITE);

	if (page == SIGNIN) {

		ColouredText("1) ", PURPLE);
		cout << "Login\n";

		ColouredText("2) ", PURPLE);
		cout << "Continue as Guest\n";

		SetColour(GRAY);
		cout << "What do (1-2): ";
	}
	else if (page == PRODUCT) {

		if (interaction == DEFAULT) {
			ColouredText("1) ", PURPLE);
			cout << "Inspect the product\n";

			ColouredText("2) ", PURPLE);
			cout << (isDescriptionShown ? "Close" : "Open") << " the description\n";

			ColouredText("3) ", PURPLE);
			cout << "Look at Reviews\n";

			ColouredText("4) ", PURPLE);
			cout << (quantityInCart == 0 ? "Add to Cart\n" : "Show in Cart\n");

			ColouredText("5)", PURPLE);
			cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";

			SetColour(GRAY);
			cout << "What do (1-5): ";

		}

		else if (interaction == QUANTITY) {
			cout << "Quantity: ";
			page = PRODUCT;
		}

		else if (interaction == BACKTOPRODUCT) {
			SetColour(WHITE);
			ColouredText("1) ", PURPLE);
			cout << "Continue Shopping\n";
			ColouredText("2) ", PURPLE);
			cout << "Continue to Cart\n";
			SetColour(GRAY);
			cout << "What do (1-2): ";
		}


	}
	else if (page == REVIEW) {
		if (interaction == DEFAULT) {
			ColouredText("1) ", PURPLE);
			cout << "Leave Review\n";
			ColouredText("2) ", PURPLE);
			cout << "Like Review\n";
			ColouredText("3) ", PURPLE);
			cout << "Dislike Review\n";
			ColouredText("4) ", PURPLE);
			cout << "Go Back\n";
			ColouredText("5)", PURPLE);
			cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";

			SetColour(GRAY);
			cout << "What do (1-5): ";
		}
		else if (interaction == LIKE) {
			cout << "Pick a review to like (1-" << product.ReviewCount() << "): ";
		}
		else if (interaction == DISLIKE) {
			cout << "Pick a review to dislike (1-" << product.ReviewCount() << "): ";
		}
	}
	else if (page == CART) {
		if (interaction == DEFAULT) {
			ColouredText("1)", PURPLE);
			cout << " Back to Product\n";
			ColouredText("2)", PURPLE);
			cout << " Proceed to Checkout\n";
			ColouredText("3)", PURPLE);
			cout << " Adjust Quantity\n";
			ColouredText("4)", PURPLE);
			cout << " Change Shipping\n";
			ColouredText("5)", PURPLE);
			cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";

			SetColour(GRAY);
			cout << "What do (1-5): ";
		}
		else if (interaction == QUANTITY){

			SetColour(GRAY);
			cout << "How much: ";
		}
	}
	else if (page == CHECKOUT) {

		if (interaction == DEFAULT) {
			ColouredText("1)", PURPLE);
			cout << " Confirm Purchase\n";
			ColouredText("2)", PURPLE);
			cout << " Head Back to Cart\n";
			ColouredText("3)", PURPLE);
			cout << " Change Shipping Address\n";
			ColouredText("4)", PURPLE);
			cout << " Change Card Number\n";
			ColouredText("5)", PURPLE);
			cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";

			SetColour(GRAY);
			cout << "What do (1-5): ";
		}
		else if (interaction == CONTINUE) {
			cout << "Leave Site\n";
			isLooping = false;
			return;
		}
		// This actually changes the card nu,
		else if (interaction == QUANTITY) {

			cout << "Changing the Card Number \nMake sure it's a between 12 and 20 digit \nNum: ";
			 
			FixedGetline(testNum);
			return;
		}
	}
	else if (page == LOGIN) {
		cout << "UserName: ";

		string thisIsWeirdIdkWhatsCausingItButThisFixesIt;
		cin >> thisIsWeirdIdkWhatsCausingItButThisFixesIt;
		getline(cin, username);
		username = thisIsWeirdIdkWhatsCausingItButThisFixesIt + username;
		return;
	}
	else if (page == SHIPPING) {

		SetColour(GRAY);
		cout << "Choose Delivery (1-3): ";
	}

	cin >> choice;
}

void main() {

	Page page = SIGNIN;
	Interactions interactions = DEFAULT;
	long long choice = 0; // I should probably come up with a better name for this

	product.AddReview(new Review("Yo Mamma", 4.5f, 3, 1, "2 Month ago", "Boot was good Boot was Red"));
	product.AddReview(new Review("Yo Dadda", 1.0f, 0, 4, "1 Month ago", "Boot was Red, I don't like Red, I don't like Boot"));
	product.AddReview(new Review("Shrek", 5.0f, 5, 1, "3 Weeks ago", "Boot so good I burried my mother in them"));
	product.AddReview(new Review("Donkey", 3.0f, 2, 1, "2 Days ago", "Maybe Boot Blue?"));

	while (isLooping) {
		system("CLS"); // Clears the Screem

		int test = stoi("10");
		string test2;
		test2[0] = '1';
		test = stoi(test2);

		try {
			//test = stoi("a");
			throw 5;
		}
		catch (int x) {

		}

		// Loads Webpage and Interactions
		LoadWebPage(page);
		LoadOutcome(page, interactions, choice);
		LoadInteractions(page, interactions, choice);
	}
	system("pause");

}