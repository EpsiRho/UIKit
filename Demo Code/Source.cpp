// UIKit Driver Program

#include <iostream>
#include <future>
#include <thread>
#include "UIKit3.h"

using namespace std;

UI::ProgressBar bar;

void fakebar() {
	COORD progress;
	progress.X = 50;
	progress.Y = 20;
	for (size_t i = 1; i <= 100; ++i) {
		bar.update(progress, i);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

int main(void) {
	// vars
	int usr_input;
	vector<string> usr_rtrn;
	bool bmenu;
	string str_input;
	char fill = 219;
	char empty = 176;
	COORD pos;
	COORD npos;
	COORD progress;
	future<void> fb;
	future<bool> an;
	progress.X = 50;
	progress.Y = 20;
	npos.X = 20;
	npos.Y = 20;
	pos.X = 40;
	pos.Y = 5;
	COORD ps = { 0,0 };
	std::vector<std::string> list = { "xbox 360", "xbox one", "xbox one x", "Playsation", "Playstation 2", "Playsation 3", "Nintendo DS", "Nintendo 3DS", "Nintendo Wii", "Nintendo Switch" };
	UI::ShowCursor();

	while (1) {
		cout << "UIKit Beta 3 Demo\n1-Grid\n2-Wrapper\n3-Color\n5-Context Menu (v3 UPDATED)\n6-Text Menu (v3 UPDATED)\n7-Path Menu (v3 UPDATED)\n8-Bool menu (v3 UPDATED)\n9-Default color (v2 UPDATED)\n10-Cursor position (v2 UPDATED)\n11-Progress Bar (v2 UPDATED)\n12-List (v3 UPDATED)\n13-Mouse Controlled Menu (Works one time then causes application to refuse input)\n14-Search Bar (v3 UPDATED)\n> ";
		cin >> usr_input;
		switch (usr_input) {
		case 1:
			UI::Grid(pos, 3, 4, "Name", "Rank", "Date Started",
						   "Jeremy", "Worker", "04/23/20",
						   "Zack", "Captain", "06/11/17",
						   "Noah", "", "TBD", NULL);
			break;
		case 2:
			UI::ClearScreen();
			UI::Wrapper(ps, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non arcu id ligula ultrices feugiat. Etiam pellentesque magna eu libero elementum auctor. Ut eu eleifend tellus, ornare sodales sapien. Mauris laoreet urna ac rutrum luctus. Suspendisse semper leo lacus, sed accumsan nulla vehicula nec. Nam posuere dui sed pretium convallis. Nulla viverra tellus ac elementum tristique. Mauris sit amet mauris enim.", 50, 1);
			break;
		case 3:
			UI::Color("this text is colored red", 12);
			break;
		case 4:
			
			break;
		case 5:
			usr_input = UI::choiceMenu(pos, "Test Menu:", "execute", "help", "connect", "disconnect", NULL);
			cout << endl << "Function Returned: " << endl;
			std::cout << usr_input;
			break;
		case 6:
			str_input = UI::textMenu(pos, "Console Test Menu");
			UI::Cursor(pos.X, pos.Y+5);
			cout << "Function Returned: " << endl;
			UI::Cursor(pos.X, pos.Y + 6);
			std::cout << str_input;
			break;
		case 7:
			usr_rtrn = UI::pathMenu(pos, "Host", "Username", "Password", NULL);
			cout << "Function Returned: " << endl;
			for (string i : usr_rtrn) {
				cout << i << endl;
			}
			break;
		case 8:
			bmenu = UI::boolMenu(pos, "Do you accept the terms of service?");
			UI::Cursor(pos.X, pos.Y + 6);
			cout << "Function Returned: " << endl;
			UI::Cursor(pos.X, pos.Y + 7);
			cout << bmenu << endl;
			break;
		case 9:
			cout << "Color: ";
			cin >> usr_input;
			UI::DefaultColor(usr_input);
			break;
		case 10:
			cout << "Setting cursor position to 40, 20";
			UI::Cursor(40, 20);
			getline(cin, str_input);
			break;
		case 11:
			bar.set_bar_width(100);
			bar.fill_bar_progress_with((char)219);
			bar.fill_bar_remainder_with((char)176);
			UI::ClearScreen();

			fb = async(&fakebar);
;			break;
		case 12:
			UI::list(pos, "To-Do", "Fix Code", "Sleep", "Sleep but again", "Sleep but this time on the couch", NULL);
			break;
		case 13:
			usr_input = UI::mouseChoiceMenu(pos, "Mouse Test", "Check 1", "Check 2", "Check 3", NULL);
			UI::Cursor(0, 0);
			UI::ClearScreen();
			cout << "Output: " << usr_input;
			break;
		case 14:
			UI::ClearScreen();
			str_input = UI::searchBar(ps, list);
			UI::ClearScreen();
			cout << "Output: " << str_input;
			break;
		default:
			cout << "Invalid Entry";
			getchar();
			UI::ClearScreen();
			break;

		}
		cin.ignore();
		getchar();
		if (!cin.good()) {
			cin.clear();
		}
		cin.clear();
		UI::ClearScreen();
	}
}