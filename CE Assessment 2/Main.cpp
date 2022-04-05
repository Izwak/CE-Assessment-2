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
};

enum Interactions {
	DEFAULT,
	QUANTITY,
	CONTINUE,
	BACKTOPRODUCT
};

Product product(
	"Boot", // Name
	120, // Cost
	20, // Shipping
	3, // Stock Count
	"This is a boot it do boot things it is red the brand is the 1 that is the good 1" // Description
);

string userName;
int quantityInCart;

bool isDescriptionShown = false;
bool isCallingSupport = false;
bool hasAdded2Cart = false;
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

Review* LeaveReview() {

	Review* newReview = new Review(userName, 0, 0, 0, "Now", "");

	while (newReview->score == 0 || newReview->comment == "") {
		system("CLS");

		ColouredText("/////Webpage////////////////////////\n\n", DARKGREEN);
		cout << "Welcome to OneStop ";
		userName != "" ? ColouredText(userName, GREEN) : ColouredText("Guest", RED);

		cout << "\n\nUser: ";
		ColouredText(newReview->user, GREEN);
		cout << ", Score: " << newReview->score << ", Date: " << newReview->date << endl;
		cout << "\tComment: \n";
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
	userName != "" ? ColouredText(userName, GREEN) : ColouredText("Guest", RED);

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

		cout << (!hasAdded2Cart ? "[Add to Cart]\n\n" : "[Show in Cart]\n\n");

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "Thank you for calling customer support. At OneStop we what to make sure that the product you get, \n";

			cout << "is the one that you want. To get a better visual of the product you can ";
			ColouredText("[Inspect the Product]", WHITE);

			cout << ". \nFor more Info about the product you can ";
			ColouredText("[Look at the Description]", WHITE);
			cout << " to find the specs.Still not sure \nif you'll like it you can ";


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
			cout << "\n\tLikes: " << review->likes << ", Dislikes: " << review->dislikes << endl << endl;

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

			cout << "Yo U got into the  cart gg\n\n";
		}

		SetColour(GRAY);
	}
	else if (page == CHECKOUT) {

		ColouredText("\n\nThank you for shoping with us at OneStop \nPlease confirm your information is correct before finalising your order\n\n", DARKGRAY);
		ColouredText("User: ", WHITE);
		ColouredText(userName, GREEN);
		cout << "\n   Product(s): \t" << product.name << " (x" << quantityInCart << ")" << endl;
		cout << "   Total Cost: \t$" << product.price * quantityInCart + product.shipping << " (Shipping Included)\n";
		cout << "   Shipping: \t$" << product.shipping << ", Default Package \n";
		cout << "   Address: \tYour Mums Basement\n";
		cout << "   ETA: \t20-25 Buisness Days\n";
		cout << "   Card Num: \t**** **** **** *321\n\n";

		// If player has called Suport display text showing what the suport is saying should change depending on page
		if (isCallingSupport) {
			ColouredText("/////Support////////////////////////\n\n", DARKGREEN);
			SetColour(DARKGRAY);

			cout << "Yo U got into the Checkout gg\n\n";

			SetColour(GRAY);
		}
	}
	else if (page == LOGIN) {
		cout << "\n\nLog in Page\n   Username: " << userName << "\n   Password: " << (userName != "" ? "*******" : "") << endl;
	}
	else {
		cout << "Oops there was a dun goof ur stuck here my b" << endl;
	}
}

void LoadOutcome(Page& page, Interactions& interaction, int& choice) {

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
				if (!hasAdded2Cart) {
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
				hasAdded2Cart = true;
				interaction = BACKTOPRODUCT;
			}
			system("pause");
		}
		else if (interaction == CONTINUE) {
			cout << "Successfully added " << choice << " to your cart\n\n";

			hasAdded2Cart = true;
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

		if (userName == "") {
			page = LOGIN;
			savedPage = REVIEW;
		}

		switch (choice)
		{
		case 1:
			if (userName == "") {
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
			if (userName == "") {
				page = LOGIN;
				savedPage = REVIEW;
				cout << "Before you can complete this action you must be signed in\n";
			}
			else {
				cout << "Like Review\n";
			}
			system("pause");
			break;
		case 3:
			if (userName == "") {
				page = LOGIN;
				savedPage = REVIEW;
				cout << "Before you can complete this action you must be signed in\n";
			}
			else {
				cout << "Dislike Review\n";
			}
			system("pause");
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
	else if (page == CART) {

		switch (choice)
		{
		case 1:
			cout << "You went back to Product\n";
			page = PRODUCT;
			break;

		case 2:
			if (userName != "") {
				cout << "You headed to the checkout\n";
				page = CHECKOUT;
			}
			else {
				cout << "Before you can Checkout you need to be signed in\n";
				page = LOGIN;
				savedPage = CHECKOUT;
			}
			break;
		case 3:
			cout << (isCallingSupport ? "You have ended" : "You have called") << " the customer support\n";
			isCallingSupport = !isCallingSupport;
			break;

		default:
			cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
			cout << "Please put in a valid choice\n";
			break;
		}

		system("pause");
	}
	else if (page == CHECKOUT) {

		switch (choice) {
		case 1:
			cout << "Confirm Purchase \nCongratulations on your purchase, come back soon!\n";
			interaction = CONTINUE;
			isInteractionShown = true;
			return;
		case 2:
			cout << " Head Back to Cart\n";
			page = CART;
			break;
		case 3:
			cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";
			isCallingSupport = !isCallingSupport;
			break;
		default:
			cout << "You didnt know what to do so you curled up in a ball and cried in a corner\n";
			cout << "Please put in a valid choice\n";
			break;
		}

		system("pause");
	}
	else if (page == LOGIN) {
		cout << "Thank you for signing in :D \nWe will now return to our reguarly scheduled program\n";
		page = savedPage;
		system("pause");
	}
}

void LoadInteractions(Page& page, Interactions& interaction, int& choice) {

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
			cout << (hasAdded2Cart ? "Show in Cart\n" : "Add to the cart\n");

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
		cout << "What do (1-4): ";
	}
	else if (page == CART) {
		ColouredText("1)", PURPLE);
		cout << " Back to Product\n";
		ColouredText("2)", PURPLE);
		cout << " Proceed to Checkout\n";
		ColouredText("3)", PURPLE);
		cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";

		SetColour(GRAY);
		cout << "What do (1-3): ";
	}
	else if (page == CHECKOUT) {

		if (interaction == DEFAULT) {
			ColouredText("1)", PURPLE);
			cout << " Confirm Purchase\n";
			ColouredText("2)", PURPLE);
			cout << " Head Back to Cart\n";
			ColouredText("3)", PURPLE);
			cout << (isCallingSupport ? " End" : " Call") << " Customer Support\n";

			SetColour(GRAY);
			cout << "What do (1-3): ";
		}
		else if (interaction == CONTINUE) {
			cout << "Leave Site\n";
			isLooping = false;
			return;
		}
	}
	else if (page == LOGIN) {
		cout << "UserName: ";
		cin >> userName;
		return;
	}

	cin >> choice;
}

void main() {

	Page page = SIGNIN;
	Interactions interactions = DEFAULT;
	int choice = 0; // I should probably come up with a better name for this

	product.AddReview(new Review("Yo Mamma", 4.5f, 3, 1, "2 Month ago", "Boot was good Boot was Red"));
	product.AddReview(new Review("Yo Dadda", 1.0f, 0, 4, "1 Month ago", "Boot was Red, I don't like Red, I don't like Boot"));
	product.AddReview(new Review("Shrek", 5.0f, 5, 1, "3 Weeks ago", "Boot so good I burried my mother in them"));
	product.AddReview(new Review("Donkey", 3.0f, 2, 1, "2 Days ago", "Maybe Boot Blue?"));

	while (isLooping) {
		system("CLS"); // Clears the Screem

		// Loads Webpage and Interactions
		LoadWebPage(page);
		LoadOutcome(page, interactions, choice);
		LoadInteractions(page, interactions, choice);
	}
	system("pause");

}