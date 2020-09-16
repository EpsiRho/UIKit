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

// UIKit Beta 3
// Written by Epsi
// Last Update: September 15, 2020

namespace UI {	
	// Clears the Console
	void ClearScreen();
	// Displays a Grid
	void Grid(COORD pos, int columns, int rows, const char* arg, ...);
	// Wraps text in user defined dimensions with or without a border
	void Wrapper(COORD pos, std::string text, int wrap, int border);
	// Colors Inputed text without changing the entire screen color
	void Color(std::string text, int clr);
	// Displays a Choice Menu and takes in an int
	int choiceMenu(COORD pos, std::string title, const char* choice, ...);
	// Displays a Choice Menu with support for mouse selection and returns an int
	int mouseChoiceMenu(COORD pos, std::string title, const char* choice, ...); 
	// Displays a Text Menu and takes in a string
	std::string textMenu(COORD pos, std::string title);
	// Displays a Pathed Menu for taking back to back input
	std::vector<std::string> pathMenu(COORD pos, const char* choice, ...);
	// Displays a menu that accpets a boolean value
	bool boolMenu(COORD pos, std::string title);
	// Sets the Default Console Color
	void DefaultColor(int clr);
	// Gets the current cursor position
	COORD GetConsoleCursorPosition();
	// Moves the console cursor to x,y
	void Cursor(int x, int y);
	// Moves the console cursor to COORD
	void Cursor(COORD destCoord);
	// Displays an updatable list [UNFINISHED]
	void list(COORD pos, std::string title, const char* item, ...);
	// Displays a Search bar
	std::string searchBar(COORD pos, std::vector<std::string> list);
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
		std::mutex mutex_;
		float progress_{ 0.0f };
		size_t bar_width_{ 60 };
		std::string fill_{ "#" }, remainder_{ " " }, status_text_{ "" };
	};
	// Hides the Cursor
	void HideCursor();
	// Shows the Cursor
	void ShowCursor();
}