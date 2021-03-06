// UIKit Beta 4 Revision 4
// Written by Epsi
// Last Update: September 24, 2020

#include "UIKit-b4.h"

// Border Defs
char vLine = 179;
char hLine = 196;
char tlCorner = 218;
char trCorner = 191;
char blCorner = 192;
char brCorner = 217;
char lGrid = 195;
char rGrid = 180;
char cGrid = 197;
char tGrid = 194;
char bGrid = 193;
char shade = 177;
constexpr char kUp = 72;
constexpr char kDown = 80;
constexpr char kLeft = 75;
constexpr char kRight = 77;
constexpr char kEnter = '\r';

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

std::wstring to_wstring(std::string str)
{
    int wchars_num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[wchars_num];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, wchars_num);
    return wstr;
}

//~~ Console Handling ~~//
void UI::clearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
void UI::color(std::string text, int clr) {
    SetConsoleTextAttribute(hout, clr);
    std::cout << text << std::endl;
    SetConsoleTextAttribute(hout, 7);
}
void UI::defaultColor(int clr) {
    SetConsoleTextAttribute(hout, clr);
}
COORD UI::getConsoleCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hout, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}
void UI::cursor(int x, int y) {
    COORD destCoord;
    destCoord.Y = y;
    destCoord.X = x;
    SetConsoleCursorPosition(hout, destCoord);
}
void UI::cursor(COORD destCoord) {
    SetConsoleCursorPosition(hout, destCoord);
}
void UI::hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hout, &info);
}
void UI::showCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 15;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void UI::enableFullscreen() {
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}
void UI::disableFullscreen() {
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
}
void UI::hideScrollbar() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hout, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(hout, new_size);
}
void UI::showScrollbar() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hout, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left,
        info.srWindow.Bottom - info.srWindow.Top
    };
    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = info.srWindow.Bottom - info.srWindow.Top - 1;
    Rect.Right = info.srWindow.Right - info.srWindow.Left;
    SetConsoleScreenBufferSize(hout, new_size);
    SetConsoleWindowInfo(hout, TRUE, &Rect);
}
void UI::setWindowSize(int Width, int Height) {
    COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    SetConsoleScreenBufferSize(hout, coord);
    SetConsoleWindowInfo(hout, TRUE, &Rect);
}
COORD UI::getWindowSize() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hout, &info);
    COORD size =
    {
        info.srWindow.Right - info.srWindow.Left,
        info.srWindow.Bottom - info.srWindow.Top
    };
    return size;
}
void UI::clearPos(int x1, int y1, int x2, int y2) {
    for (int i = 0; i <= y2 - y1; i++) {
        for (int k = 0; k <= x2 - x1; k++) {
            UI::cursor(x1 + k, y1 + i);
            std::cout << " ";
        }
    }
}
void UI::refresh(int x1, int y1, int x2, int y2, std::string chars) {
    int count = 0;
    for (int i = 0; i <= y2 - y1; i++) {
        for (int k = 0; k <= x2 - x1; k++) {
            UI::cursor(x1 + k, y1 + i);
            std::cout << chars[count];
            count++;
        }
    }
}

//~~ Font Handling ~~//
void UI::setFontSize(int FontSize)
{
    CONSOLE_FONT_INFOEX info = { 0 };
    GetCurrentConsoleFontEx(hout, FALSE, &info);
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = FontSize;
    //info.FontWeight = FW_NORMAL;
    //wcscpy(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
}
void UI::setFont(std::string font) {
    CONSOLE_FONT_INFOEX info = { 0 };
    _CONSOLE_FONT_INFO fontinfo = { 0 };
    GetCurrentConsoleFontEx(hout, FALSE, &info);
    GetCurrentConsoleFont(hout, FALSE, &fontinfo);
    COORD fntSize = GetConsoleFontSize(hout, fontinfo.nFont);
    //std::cout << fntSize.X << " / " << fntSize.Y;
    info.cbSize = sizeof(info);
    info.dwFontSize.X = fntSize.X;
    info.dwFontSize.Y = fntSize.Y;
    //info.FontFamily = FF_DONTCARE;
    //info.FontWeight = FW_NORMAL;
    std::wstring str = to_wstring(font);
    lstrcpyW(info.FaceName, str.c_str());
    std::wstring fuck = info.FaceName;
    //std::wcout << info.FaceName << fuck.size();
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
}

//~~ Text Formatting ~~//
void UI::grid(COORD pos, int columns, int rows, const char* arg, ...) {
    // Vars
    std::vector<std::string> items;
    std::vector<int> longest;
    int gridL = 2;
    int temp = 0;
    std::string pass;
    int itemCount = 0;

    // Grab strings from function args
    va_list arguments;
    for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char*)) {
        pass = arg;
        items.push_back(pass);
    }
    va_end(arguments);

    // Find largest string in each column
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            if (temp < items[i + (columns * j)].size()) {
                temp = items[i + (columns * j)].size();
            }
        }
        longest.push_back(temp);
        temp = 0;
    }

    // Output the Top of the grid
    cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; gridL++; }
        if (i < columns - 1) {
            std::cout << tGrid;
        }
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Rows
    cursor(pos.X, pos.Y);
    for (int i = 0; i < rows; i++) {
        std::cout << vLine << " ";
        for (int j = 0; j < columns; j++) {
            std::cout << items[itemCount];
            for (int k = items[itemCount].size(); k <= longest[0 + j]; k++) {
                std::cout << " ";
            }
            std::cout << vLine << " ";
            itemCount++;
        }
        std::cout << std::endl;
        pos.Y++;
        cursor(pos.X, pos.Y);
        if (i < rows - 1) {
            std::cout << lGrid;
            for (int i = 0; i < columns; i++) {
                for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; gridL++; }
                if (i < columns - 1) {
                    std::cout << cGrid;
                }
            }
            std::cout << rGrid << std::endl;
        }
        pos.Y++;
        cursor(pos.X, pos.Y);
    }
    pos.Y--;
    // Output Bottom of the grid
    cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; }
        if (i < columns - 1) {
            std::cout << bGrid;
        }
    }
    std::cout << brCorner << std::endl;

}
void UI::wrapper(COORD pos, std::string text, int wrap, int border) {
    // Vars
    int place = 0;

    switch (border) {
    case 0: // Output without a border
        // Output Wrapped Text

        for (int i = 0; i < text.size(); i += wrap) {
            cursor(pos.X, pos.Y);
            for (int k = place; k < (place + wrap); k++) {
                if (k >= text.size()) {
                    std::cout << " ";
                }
                else {
                    std::cout << text[k];
                }
            }
            place += wrap;
            pos.Y++;
            cursor(pos.X, pos.Y);
        }
        break;
    case 1: // Output With a border
        // Output Top Border
        cursor(pos.X, pos.Y);
        std::cout << tlCorner;
        for (int i = 0; i < wrap + 2; i++) {
            std::cout << hLine;
        }
        std::cout << trCorner << std::endl;
        pos.Y++;

        // Output Wrapped Text
        for (int i = 0; i < text.size(); i += wrap) {
            cursor(pos.X, pos.Y);
            std::cout << vLine << " ";
            for (int k = place; k < (place + wrap); k++) {
                if (k >= text.size()) {
                    std::cout << " ";
                }
                else {
                    std::cout << text[k];
                }
            }
            std::cout << " " << vLine << std::endl;
            place += wrap;
            pos.Y++;
            cursor(pos.X, pos.Y);
        }

        cursor(pos.X, pos.Y);
        // Output Bottom Border
        std::cout << blCorner;
        for (int i = 0; i < wrap + 2; i++) {
            std::cout << hLine;
        }
        std::cout << brCorner << std::endl;
        break;
    }
}
void UI::list(COORD pos, std::string title, const char* item, ...) {
    // Vars
    std::vector<std::string> items;
    int longest;
    std::string pass;

    // Grab strings from function args
    va_list arguments;
    for (va_start(arguments, item); item != NULL; item = va_arg(arguments, const char*)) {
        pass = item;
        items.push_back(pass);
    }
    va_end(arguments);

    // Get Longest string
    pass = items[0];
    longest = pass.size();
    for (int i = 1; i < items.size(); i++) {
        if (pass.size() < items[i].size()) {
            pass = items[i];
            longest = pass.size();
        }
    }

    // Output the Top of the Menu
    cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < longest + 3; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Title
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title;
    for (int i = title.size(); i < longest + 2; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    cursor(pos.X, pos.Y);
    std::cout << lGrid;
    for (int i = 0; i < longest + 3; i++) {
        std::cout << hLine;
    }
    std::cout << rGrid << std::endl;
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[i];
        for (int j = items[i].size(); j < longest + 2; j++) {
            std::cout << " ";
        }
        std::cout << vLine << std::endl;
        pos.Y++;
        cursor(pos.X, pos.Y);

    }

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < longest + 3; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;


}
void UI::copyToClipboard(std::string str) {
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, str.length() + 1);
    memcpy(GlobalLock(hMem), str.c_str(), str.length() + 1);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}
std::string UI::copyFromClipboard() {
    OpenClipboard(nullptr);
    HANDLE hData = GetClipboardData(CF_TEXT);
    char* pszText = static_cast<char*>(GlobalLock(hData));
    std::string text(pszText);
    GlobalUnlock(hData);
    CloseClipboard();
    return text;
}

//~~ Menus ~~//
int UI::choiceMenu(COORD pos, std::string title, const char* choice, ...) {
    // Vars
    std::string pass;
    std::vector<std::string> items;
    int longest;
    int usr_input;
    COORD loc;
    char in = ' ';
    int menupos;
    hideCursor();
    // Grab Function Args
    va_list arguments;
    for (va_start(arguments, choice); choice != NULL; choice = va_arg(arguments, const char*)) {
        pass = choice;
        items.push_back(pass);
    }
    va_end(arguments);

    // Get Longest string
    pass = items[0];
    longest = pass.size();
    for (int i = 1; i < items.size(); i++) {
        if (pass.size() < items[i].size()) {
            pass = items[i];
            longest = pass.size();
        }
    }
    if (longest < title.size()) {
        longest = title.size();
    }

    // Output the Top of the Menu
    cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Title
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title;
    for (int i = title.size(); i < longest + 5; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    cursor(pos.X, pos.Y);
    std::cout << lGrid;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << rGrid << std::endl;
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[i];
        for (int j = items[i].size(); j < longest + 2; j++) {
            std::cout << " ";
        }
        std::cout << "( )" << vLine << std::endl;
        pos.Y++;
        cursor(pos.X, pos.Y);
        
    }

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;


    // User input
    menupos = 1;
    loc = getConsoleCursorPosition();
    COORD home = loc;
    while (in != '\r') {
        cursor(loc.X - 3, loc.Y - items.size() - 1);
        home = getConsoleCursorPosition();
        for (int i = 1; i <= items.size(); i++) {
            cursor(home.X, home.Y + i );
            if (i == menupos) {
                std::cout << menupos;
            }
            else {
                std::cout << " ";
            }
            cursor(loc.X, loc.Y);
        }

        in = _getch();
        switch (in) {
        case kUp:
            if (menupos != 1) {
                menupos--;
            }
            break;
        case kDown:
            if (menupos != items.size()) {
                menupos++;
            };
        }
    }
    showCursor();
    return menupos;
}
std::string UI::textMenu(COORD pos, std::string title) {
    // Vars
    COORD origionLoc;
    COORD loc;
    char in = ' ';
    char last = ' ';
    std::string finished = "";
    int cur;
    //ClearScreen();
    //HideCursor();

    // Output the Top of the Menu
    cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < title.size() + finished.size() + 4; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output center
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title << ":" << finished << "  " << vLine << std::endl;
    pos.Y++;

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < title.size() + finished.size() + 4; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;
    pos.Y++;
    cursor(pos.X, pos.Y);
    std::cout << "> ";
    //Update Border
    //std::cin.ignore();
    getline(std::cin, finished);
    return finished;
}
std::vector<std::string> UI::pathMenu(COORD pos, const char* choice, ...) {
    // Vars
    std::string pass;
    std::vector<std::string> items;
    std::vector<std::string> send;
    char in = ' ';
    std::string finished = "";
    int longest;
    int usr_input;
    COORD origionLoc = pos;
    COORD loc;

    hideCursor();

    // Grab Function Args
    va_list arguments;
    for (va_start(arguments, choice); choice != NULL; choice = va_arg(arguments, const char*)) {
        pass = choice;
        items.push_back(pass);
    }
    va_end(arguments);

    for (int a = 0; a < items.size(); a++) {

        //ClearScreen();
        // Output the Top of the Menu
        cursor(pos.X, pos.Y);
        std::cout << tlCorner;
        for (int i = 0; i < items[a].size() + finished.size() + 4; i++) {
            std::cout << hLine;
        }
        std::cout << trCorner << std::endl;
        pos.Y++;

        // Output center
        cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[a] << ": " << finished << " " << vLine << std::endl;
        pos.Y++;

        // Output the Bottom of the Menu
        cursor(pos.X, pos.Y);
        std::cout << blCorner;
        for (int i = 0; i < items[a].size() + finished.size() + 4; i++) {
            std::cout << hLine;
        }
        std::cout << brCorner << std::endl;
        pos.Y++;

        // Update Menu Border
        while (in != '\r') {
            cursor(pos.X, pos.Y);
            in = _getch();
            if (in == '\b' && finished.size() > 0) {
                finished.erase(finished.begin() + finished.size() - 1);
                origionLoc = getConsoleCursorPosition();
                loc = origionLoc;
                cursor(loc.X + (finished.size() + items[a].size()) + 5, loc.Y - 3);
                std::cout << hLine << trCorner << " " << "  ";
                loc = getConsoleCursorPosition();
                cursor(loc.X - finished.size() - 5, loc.Y + 1);
                std::cout << finished << " " << vLine << "     ";;
                loc = getConsoleCursorPosition();
                cursor(loc.X - 7, loc.Y + 1);
                std::cout << hLine << brCorner << " " << "  ";
                cursor(origionLoc.X, origionLoc.Y);
            }
            else if(in != '\b' && in != '\r'){
                finished += in;
                origionLoc = getConsoleCursorPosition();
                loc = origionLoc;
                cursor(loc.X + (finished.size() + items[a].size()) + 3, loc.Y - 3);
                std::cout << hLine << hLine << hLine << trCorner;
                loc = getConsoleCursorPosition();
                cursor(loc.X - finished.size() - 2, loc.Y + 1);
                std::cout << finished << " " << vLine;
                loc = getConsoleCursorPosition();
                cursor(loc.X - 3, loc.Y + 1);
                std::cout << hLine << hLine << brCorner;
                cursor(origionLoc.X, origionLoc.Y);
            }
        }
        //finished.erase(finished.begin() + finished.size() - 1);
        send.push_back(finished);
        in = ' ';
        finished = "";
    }
    clearScreen();
    showCursor();
    return send;
}
bool UI::boolMenu(COORD pos, std::string title) {
    // Vars
    bool choice = true;
    char ch = ' ';
    COORD loc;
    hideCursor();
    //ClearScreen();

    // Output Top Bar
    cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < title.size() + 2; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Center
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title << " " << vLine << std::endl;
    pos.Y++;
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << "(*) Yes"; 
    for (int i = 0; i < title.size() - 8 + 2; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << "( ) No";
    for (int i = 0; i < title.size() - 7 + 2; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;

    // Output Bottom Bar
    cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < title.size() + 2; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;

    while (1) {
        switch (choice) {
        case true:
            loc = getConsoleCursorPosition();
            cursor(loc.X - title.size() - 1, loc.Y - 2);
            std::cout << "*";
            cursor(loc.X - title.size() - 1, loc.Y - 1);
            std::cout << " ";
            cursor(loc.X, loc.Y);
            break;
        case false:
            loc = getConsoleCursorPosition();
            cursor(loc.X - title.size() - 1, loc.Y - 2);
            std::cout << " ";
            cursor(loc.X - title.size() - 1, loc.Y - 1);
            std::cout << "*";
            cursor(loc.X, loc.Y);
            break;
        }
        ch = _getch();
        switch (ch) {
        case kUp:
            choice = true;
            break;
        case kDown:
            choice = false;
            break;
        case kEnter:
            return choice;
            break;
        }
    }
    showCursor();
}
std::string UI::searchBar(COORD pos, std::vector<std::string> list) {
    // Vars
    int longest;
    std::string pass;
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InputRecord;
    DWORD Events;
    char in;
    COORD tPos = { 0,0 };
    COORD smpos = pos;
    smpos.X++;
    smpos.Y++;
    std::string input;
    std::vector<std::string> temp;
    int count = 0;
    int menupos = 0;

    // Get Longest string
    pass = list[0];
    longest = pass.size();
    for (int i = 1; i < list.size(); i++) {
        if (pass.size() < list[i].size()) {
            pass = list[i];
            longest = pass.size();
        }
    }
    for (int i = 0; i < list.size(); i++) {
        for (int k = 0; k < list[i].length(); k++) {
            list[i][k] = std::toupper(list[i][k]);
        }
    }

    UI::cursor(pos.X, pos.Y);
    std::cout << ">";

    while (1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if (InputRecord.EventType == KEY_EVENT) {
            if (InputRecord.Event.KeyEvent.bKeyDown) {
                in = InputRecord.Event.KeyEvent.wVirtualKeyCode;
                if (in == 0x08 && input.size() > 0) {
                    tPos = UI::getConsoleCursorPosition();
                    UI:cursor(tPos.X-1, tPos.Y);
                    std::cout << " ";
                    UI::cursor(pos.X + 1, pos.Y+1);
                    for (int i = 0; i < 8; i++) {
                        for (int k = 0; k < longest+6; k++) {
                            std::cout << " ";
                        }
                        std::cout << "\n";
                    }
                    UI::cursor(pos.X + 1, pos.Y);
                    input.pop_back();
                    std::cout << input;
                }
                else if (in == VK_DOWN && input.size() > 0) {
                    menupos = 1;
                    UI::cursor(smpos.X, smpos.Y+menupos);
                    std::cout << (char)254;
                    while (menupos > 0) {
                        ReadConsoleInput(hin, &InputRecord, 1, &Events);
                        if (InputRecord.EventType == KEY_EVENT) {
                            if (InputRecord.Event.KeyEvent.bKeyDown) {
                                in = InputRecord.Event.KeyEvent.wVirtualKeyCode;
                                for (int i = 1; i < temp.size()+1; i++) {
                                    UI::cursor(smpos.X, smpos.Y + i);
                                    std::cout << " ";
                                }
                                if (in == VK_UP) {
                                    menupos--;
                                }
                                else if (in == VK_DOWN && menupos < temp.size()) {
                                    menupos++;
                                }
                                else if (in == 0x0D) {
                                    return temp[menupos-1];
                                }
                                UI::cursor(smpos.X, smpos.Y + menupos);
                                std::cout << (char)254;
                            }
                        }
                    }
                    UI::cursor(tPos.X, tPos.Y);
                }
                else if (in == 0x0D) {
                    
                }
                else if(in != 0x08){
                    UI::cursor(pos.X + 1, pos.Y+1);
                    for (int i = 0; i < 8; i++) {
                        for (int k = 0; k < longest+6; k++) {
                            std::cout << " ";
                        }
                        std::cout << "\n";
                    }
                    UI::cursor(pos.X + 1, pos.Y);
                    input.push_back(in);
                    std::cout << input;
                }
            }
            count = 0;
            temp.clear();
            if (input.size() >=! 0) {
                for (int i = 0; i < list.size(); i++) {
                    if (list[i].find(input) != std::string::npos && count <= 5) {
                        temp.push_back(list[i]);
                        count++;
                    }
                }
            }
            tPos = UI::getConsoleCursorPosition();
            COORD mPos = pos;
            mPos.Y++;
            // Output the Top of the Menu
            cursor(mPos.X, mPos.Y);
            std::cout << tlCorner;
            for (int i = 0; i < longest + 3; i++) {
                std::cout << hLine;
            }
            std::cout << trCorner << std::endl;
            mPos.Y++;

            // Output Choices
            for (int i = 0; i < temp.size(); i++) {
                cursor(mPos.X, mPos.Y);
                std::cout << vLine << " " << temp[i];
                for (int j = temp[i].size(); j < longest + 2; j++) {
                    std::cout << " ";
                }
                std::cout << vLine << std::endl;
                mPos.Y++;
                cursor(mPos.X, mPos.Y);

            }

            // Output the Bottom of the Menu
            cursor(mPos.X, mPos.Y);
            std::cout << blCorner;
            for (int i = 0; i < longest + 3; i++) {
                std::cout << hLine;
            }
            std::cout << brCorner;
            UI::cursor(tPos.X, tPos.Y);
        }
    }
}

//~~ Progress Bars ~~//
void UI::ProgressBar::set_progress(float value) {
    std::unique_lock lock{ mutex_ };  // CTAD (C++17)
    progress_ = value;
}
void UI::ProgressBar::set_bar_width(size_t width) {
    std::unique_lock lock{ mutex_ };
    bar_width_ = width;
}
void UI::ProgressBar::fill_bar_progress_with(const char& ch) {
    std::unique_lock lock{ mutex_ };
    fill_ = ch;
}
void UI::ProgressBar::fill_bar_remainder_with(const char& ch) {
    std::unique_lock lock{ mutex_ };
    remainder_ = ch;
}
void UI::ProgressBar::set_status_text(const std::string& status) {
    std::unique_lock lock{ mutex_ };
    status_text_ = status;
}
void UI::ProgressBar::update(COORD pos, float value) {
    std::ostream& os = std::cout;
    cursor(pos.X, pos.Y);
    set_progress(value);
    write_progress(pos);
}
void UI::ProgressBar::write_progress(COORD pos) {
    std::ostream& os = std::cout;
    std::unique_lock lock{ mutex_ };

    // No need to write once progress is 100%
    if (progress_ > 100.0f) return;

    // Move cursor to the first position on the same line and flush 
    cursor(pos.X, pos.Y);

    // Start bar
    os << "[";

    const auto completed = static_cast<size_t>(progress_ * static_cast<float>(bar_width_) / 100.0);
    for (size_t i = 0; i < bar_width_; ++i) {
        if (i <= completed)
            os << fill_;
        else
            os << remainder_;
    }

    // End bar
    os << "]";

    // Write progress percentage
    os << " " << std::min(static_cast<size_t>(progress_), size_t(100)) << "%";

    // Write status text
    os << " " << status_text_;
}

//~~ Mouse Handling ~~//
bool mouseEnabled = false;
void UI::enableMouseHandling() {
    SetConsoleMode(hin, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    mouseEnabled = true;
}
void UI::disabledMouseHandling() {
    SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    mouseEnabled = false;
}
COORD UI::getMousePos() {
    INPUT_RECORD InputRecord;
    DWORD Events;
    ReadConsoleInput(hin, &InputRecord, 1, &Events);
    return InputRecord.Event.MouseEvent.dwMousePosition;
}
COORD UI::waitForClick() {
    INPUT_RECORD InputRecord;
    DWORD Events;
    while (1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        COORD p = InputRecord.Event.MouseEvent.dwMousePosition;
        if (InputRecord.EventType == MOUSE_EVENT) {
            if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                return p;
            }
        }
    }
}
bool UI::posInArea(COORD pos, int x1, int y1, int x2, int y2) {
    if (pos.X >= x1 && pos.X <= x2 && pos.Y >= y1 && pos.Y <= y2) {
        return true;
    }
    return false;
}
int clipDestroy = 0;
void UI::clipboardText(COORD pos, std::string text, std::string copy) {
    INPUT_RECORD InputRecord;
    DWORD Events;
    hideCursor();

    // Move cursor to the specified position
    cursor(pos);
    // Print the specified text
    color(text, 15);

    // Enter a loop to check if the mouse is over the text
    while (clipDestroy == 0){
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        COORD p = InputRecord.Event.MouseEvent.dwMousePosition;
        if (p.X >= pos.X && p.X <= pos.X+text.length() && pos.Y == p.Y) {
            cursor(pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            std::cout << text;
        }
        else {
            cursor(pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            std::cout << text;
        }
        if (InputRecord.EventType == MOUSE_EVENT) {
            if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                if (p.X >= pos.X && p.X <= pos.X + text.length() && pos.Y == p.Y) {
                    copyToClipboard(copy);
                }
            }
        }
    }
    clipDestroy = 0;
}
void UI::clipboardEnd() {
    clipDestroy = 1;
}
int UI::mouseChoiceMenu(COORD pos, std::string title, const char* choice, ...) {
    // Vars
    std::string pass;
    std::vector<std::string> items;
    int longest;
    int usr_input;
    COORD loc;
    char in = ' ';
    int menupos;

    hideCursor();
    if (mouseEnabled != true) {
        return -1;
    }

    // Grab Function Args
    va_list arguments;
    for (va_start(arguments, choice); choice != NULL; choice = va_arg(arguments, const char*)) {
        pass = choice;
        items.push_back(pass);
    }
    va_end(arguments);

    // Get Longest string
    pass = items[0];
    longest = pass.size();
    for (int i = 1; i < items.size(); i++) {
        if (pass.size() < items[i].size()) {
            pass = items[i];
            longest = pass.size();
        }
    }
    if (longest < title.size()) {
        longest = title.size();
    }

    //SetConsoleTextAttribute(hout, 15);

    // Output the Top of the Menu
    cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Title
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title;
    for (int i = title.size(); i < longest + 5; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    cursor(pos.X, pos.Y);
    std::cout << lGrid;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << rGrid << std::endl;
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[i];
        for (int j = items[i].size(); j < longest + 2; j++) {
            std::cout << " ";
        }
        std::cout << "   " << vLine << std::endl;
        pos.Y++;
        cursor(pos.X, pos.Y);

    }

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;


    // User input
    menupos = 1;
    loc = getConsoleCursorPosition();
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD home = loc;
    char sel = 219;
    char ptr = 221;
    char clk = 237;
    std::deque<COORD> points;
    home.X = home.X - 3;
    for (int i = 0; i < items.size(); i++) {
        home.Y--;
        points.push_front(home);
    }
    while (1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        COORD p = InputRecord.Event.MouseEvent.dwMousePosition;
        for (int i = 0; i < points.size(); i++) {
            UI::cursor(points[i].X - longest - 3, points[i].Y);
            SetConsoleTextAttribute(hout, 8);
            //std::cout << sel << ptr;
            std::cout << items[i];
        }
        for (int i = 0; i < points.size(); i++) {
            if (p.X >= points[i].X - longest - 2 && p.X <= points[i].X && p.Y == points[i].Y) {
                UI::cursor(points[i].X - longest - 3, points[i].Y);
                SetConsoleTextAttribute(hout, 11);
                //std::cout << sel << ptr;
                std::cout << items[i];
            }
        }
        if (InputRecord.EventType == MOUSE_EVENT) {
            if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                for (int i = 0; i < points.size(); i++) {
                    if (p.X >= points[i].X - longest - 2 && p.X <= points[i].X && p.Y == points[i].Y) {
                        UI::cursor(points[i].X - longest - 4, points[i].Y);
                        SetConsoleTextAttribute(hout, 187);
                        std::cout << " " << items[i];
                        for (int k = items[i].size(); k < longest + 2; k++) {
                            std::cout << " ";
                        }
                        std::cout << "   ";
                        UI::cursor(p.X, (p.Y+4) - i);
                        showCursor();
                        SetConsoleTextAttribute(hout, 15);
                        return i;
                    }
                }
            }
        }
    }


}
