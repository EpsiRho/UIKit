// UIKit Beta 5 Revision 5
// Written by Epsi
// Last Update: October 9, 2020

#pragma once
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <atomic>
#include <mutex>
#include <algorithm>
#include <deque>
#include <locale>
#include <codecvt>
#include <cstdint> 
#include <fstream>

namespace UI {	
//~~ Console Handling ~~//
	// Clears the Console
	void clearScreen();
	// Colors Inputed text without changing the entire screen color
	void color(std::string text, int clr);
	// Sets the Default Console Color
	void defaultColor(int clr);
	// Gets the current cursor position
	COORD getConsoleCursorPosition();
	// Moves the console cursor to x,y
	void cursor(int x, int y);
	// Moves the console cursor to COORD
	void cursor(COORD destCoord);
	// Hides the Cursor
	void hideCursor();
	// Shows the Cursor
	void showCursor();
	// Activates Fullscreen on the terminal window
	void enableFullscreen();
	// Deactivates Fullscreen on the terminal window
	void disableFullscreen();
	// Removes the scrollbar
	void hideScrollbar();
	// Shows the scrollbar
	void showScrollbar();
	// Set console window size
	void setWindowSize(int Width, int Height);
	// gets the window size x, y(width, height)
	COORD getWindowSize();
	void clearPos(int x1, int y1, int x2, int y2);
	void refresh(int x1, int y1, int x2, int y2, std::string chars);
	void scrollConsoleBuffer(int x1, int y1, int x2, int y2, int x3, int y3);

//~~ Font Handling ~~//
	void setFontSize(int FontSize);
	void setFont(std::string font);

//~~ Text Formating ~~//
	// Displays a Grid
	void grid(COORD pos, int columns, int rows, const char* arg, ...);
	// Wraps text in user defined dimensions with or without a border
	void wrapper(COORD pos, std::string text, int wrap, int border);
	// Displays a list
	void list(COORD pos, std::string title, const char* item, ...);
	// Copies a string to the clipboard
	void copyToClipboard(std::string str);
	std::string copyFromClipboard();
	void editFile(std::string filepath);
	
//~~ Menus ~~//
	// Displays a Choice Menu and takes in an int
	int choiceMenu(COORD pos, std::string title, const char* choice, ...);
	// Displays a Text Menu and takes in a string
	std::string textMenu(COORD pos, std::string title);
	// Displays a Pathed Menu for taking back to back input
	std::vector<std::string> loginMenu(COORD pos, std::string title, const char* choice, ...);
	// Displays a menu that accpets a boolean value
	bool boolMenu(COORD pos, std::string title);
	// Displays a Search bar
	std::string searchBar(COORD pos, std::vector<std::string> list);
	
//~~ Progress Bars ~~//
	// Displays a Progress Bar
	class ProgressBar {
	public:
		void set_progress(float value);
		void set_bar_width(size_t width);
		void fill_bar_progress_with(const char& ch);
		void fill_bar_remainder_with(const char& ch);
		void set_status_text(const std::string& status);
		void update(COORD pos, float value);
		void write_progress(COORD pos);
	private:
		float progress_{ 0.0f };
		size_t bar_width_{ 60 };
		std::string fill_{ "#" }, remainder_{ " " }, status_text_{ "" };
	};
	
//~~ Mouse Handling ~~//
	// Enables Mouse Handling(And disables Quick Edit and Line input)
	void enableMouseHandling();
	// Disables Mouse Handling(And enables Quick Edit and Line Input)
	void disabledMouseHandling();
	// Returns a COORD with the current mouse position
	COORD getMousePos();
	// Waits for the user to click
	COORD waitForClick();
	// Checks to see if a coord is within a bounding box
	bool posInArea(COORD pos, int x1, int y1, int x2, int y2);
	// Creates text that can be clicked to copy to the clipboard
	void clipboardText(COORD pos, std::string text, std::string copy);
	// Stops a clipboard text button
	void clipboardEnd();
	// Displays a Choice Menu with support for mouse selection and returns an int
	int mouseChoiceMenu(COORD pos, std::string title, const char* choice, ...);
}