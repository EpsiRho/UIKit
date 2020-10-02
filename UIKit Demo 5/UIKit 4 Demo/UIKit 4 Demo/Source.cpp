// UIKit Beta 5 Revision 4 Demo Application
// Written by Epsi
// Last Update: October 2, 2020

#include <iostream>
#include <windows.h>
#include <future>
#include "UIKit-b5.h"

using namespace std;

int main(void) {
    UI::enableFullscreen(); // Send the application to fullscreen
	UI::hideCursor(); // Hide the console's cursor
	UI::defaultColor(15); // set the color to be bright white
	UI::setFontSize(32); 

	// Variables
	bool uBool = false;
	vector<string> usr_rtrn;
	vector<string> list = {
		"Wii",
		"Wii U",
		"Xbox 360",
		"Xbox One",
		"Dreamcast",
		"Nintendo 64",
		"PlayStation",
		"PlayStation 2",
		"PlayStation 3",
		"PlayStation 4",
		"Sega Genesis",
		"Nintendo DS",
		"Nintendo DSI",
		"Nintendo 3DS",
		"Nintendo Switch",
		"Atari 7800"
	};
	UI::ProgressBar bar;
	COORD pos = { 0,0 };
	COORD pbPos = { 0,1 };

	// Main Loop
	while (1) {
		UI::enableMouseHandling(); // Enable Mouse Handling Mode
		int usr_input = UI::mouseChoiceMenu(pos, "UIKit Demo (Page 1)", "Exit", "Bool Menu", "Choice Menu", "Clipboard", "Color", "Cursor Handling", 
												 "Font Handling", "Grids", "List", "Login Menu", "Progress Bars", "Search Bar", "Text Menu",NULL);
		switch (usr_input) {
			case 0:
				exit(1);
				break;
			case 1:
				UI::disabledMouseHandling();
				UI::clearScreen();
				uBool = UI::boolMenu(pos, "Do you Accept?");
				UI::clearScreen();
				break;
			case 2:
				UI::disabledMouseHandling();
				UI::clearScreen();
				UI::choiceMenu(pos, "Favorite Color", "Red", "Orange", "Yellow", "Green", "Blue", "purple", NULL);
				UI::clearScreen();
				break;
			case 3:
				UI::cursor(0, 3);
				UI::clearScreen();
				UI::copyToClipboard("Hello World!");
				UI::color("Text coppied to clipboard!", 143);
				Sleep(1000);
				UI::clearScreen();
				break;
			case 4:
				UI::clearScreen();
				while (1) {
					int usr_input = UI::mouseChoiceMenu(pos, "Color Demo", "<--Back", "Blue", "Green", "Light Blue", "Red", "Purple", "Yellow", "White", NULL);
					if (usr_input == 0) {
						break;
					}
					UI::defaultColor(usr_input+8);

				}
				UI::clearScreen();
				break;
			case 5:
				UI::clearScreen();
				UI::cursor(30, 0);
				cout << "Oh no dropped all my blocks!";
				for (int i = 0; i < 50; i++) {
					int rx = rand() % 100;
					int ry = rand() % 40 + 1;
					UI::cursor(rx, ry);
					cout << (char)219;
				}
				break;
			case 6:
				for (int i = 20; i < 50; i++) {
					UI::setFontSize(i);
					Sleep(10);
				}
				for (int i = 50; i > 20; i--) {
					UI::setFontSize(i);
					Sleep(10);
				}
				for (int i = 20; i < 32; i++) {
					UI::setFontSize(i);
					Sleep(10);
				}
				break;
			case 7:
				UI::clearScreen();
				UI::grid(pos, 3, 4, "Name", "Rank", "Date Started",
					"Jeremy", "Worker", "04/23/20",
					"Zack", "Captain", "06/11/17",
					"Noah", "", "TBD", NULL);
				_getch();
				UI::clearScreen();
				break;
			case 8:
				UI::clearScreen();
				UI::list(pos, "To-Do", "Fix Code", "Sleep", "Sleep but again", "Sleep but this time on the couch", NULL);
				_getch();
				UI::clearScreen();
				break;
			case 9:
				UI::disabledMouseHandling();
				UI::clearScreen();
				usr_rtrn = UI::loginMenu(pos, "FTP Login", "Host", "Username", "Password", NULL);
				UI::clearScreen();
				UI::enableMouseHandling();
				break;
			case 10:
				UI::clearScreen();
				bar.set_bar_width(60);
				bar.fill_bar_progress_with((char)219);
				bar.fill_bar_remainder_with((char)176);
				bar.set_status_text("Scanning");
				cout << "Uploading:";
				for (int i = 0; i <= 100; i++) {
					bar.update(pbPos, i);
					if (i >= 35 && i <= 36) {
						bar.set_status_text("Zipping");
					}
					else if (i >= 51 && i <= 52) {
						bar.set_status_text("Uploading");
					}
					else if (i >= 89 && i <= 90) {
						bar.set_status_text("Finalizing");
					}
					Sleep(10+i);
				}
				break;
			case 11:
				UI::clearScreen();
				UI::hideCursor();
				cout << "Type to search, hit the down arrow to select";
				UI::searchBar(pbPos, list);
				UI::clearScreen();
				break;
			case 12:
				UI::disabledMouseHandling();
				UI::clearScreen();
				UI::textMenu(pos, "Enter your name");
				UI::clearScreen();
				UI::enableMouseHandling();
				UI::clearScreen();
				break;
		}
	}
}