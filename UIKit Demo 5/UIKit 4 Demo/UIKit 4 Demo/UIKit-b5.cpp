// UIKit Beta 5 Revision 5
// Written by Epsi
// Last Update: October 9, 2020

#include "UIKit-b5.h"

// Border Defs
constexpr char vLine = (char)179;
constexpr char hLine = (char)196;
constexpr char tlCorner = (char)218;
constexpr char trCorner = (char)191;
constexpr char blCorner = (char)192;
constexpr char brCorner = (char)217;
constexpr char lGrid = (char)195;
constexpr char rGrid = (char)180;
constexpr char cGrid = (char)197;
constexpr char tGrid = (char)194;
constexpr char bGrid = (char)193;
constexpr char shade = (char)177;
constexpr char cube = (char)254;
constexpr char lHalf = (char)221;
constexpr char kUp = (char)72;
constexpr char kDown = (char)80;
constexpr char kLeft = (char)75;
constexpr char kRight = (char)77;
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
    if (hStdOut == INVALID_HANDLE_VALUE) {
        return;
    }

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) { 
        return; 
    }
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces 
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) {
        return;
    }

    // Fill the entire buffer with the current colors and attributes 
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) {
        return;
    }

    // Move the cursor home 
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
void UI::color(std::string text, int clr) {
    SetConsoleTextAttribute(hout, clr);
    fwrite(text.c_str(), text.size() + 1, 1, stdout);
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
            fwrite(" ", 1, 1, stdout);
        }
    }
}
void UI::refresh(int x1, int y1, int x2, int y2, std::string chars) {
    int count = 0;
    for (int i = 0; i <= y2 - y1; i++) {
        for (int k = 0; k <= x2 - x1; k++) {
            UI::cursor(x1 + k, y1 + i);
            fwrite(&chars[count], 1, 1, stdout);
            count++;
        }
    }
}
void UI::scrollConsoleBuffer(int x1, int y1, int x2, int y2, int x3, int y3) {
    SMALL_RECT srctScrollRect, srctClipRect;
    CHAR_INFO chiFill;
    COORD coordDest;

    // The scrolling rect

    srctScrollRect.Left = x1;
    srctScrollRect.Top = y1;
    srctScrollRect.Right = x2;
    srctScrollRect.Bottom = y2;

    // The destination for the scroll rect
    coordDest.X = x3;
    coordDest.Y = y3;

    // Clipping rect is the same as the scrooling rect
    srctClipRect = srctScrollRect;

    // Fill the bottom row with blanks. 
    chiFill.Attributes = 0;
    chiFill.Char.AsciiChar = ' ';

    // Scroll
    if (!ScrollConsoleScreenBufferA(
        hout,         // screen buffer handle 
        &srctScrollRect, // scrolling rectangle 
        &srctClipRect,   // clipping rectangle 
        coordDest,       // top left destination cell 
        &chiFill))       // fill character and color
    {
        return;
    }
}

//~~ Font Handling ~~//
void UI::setFontSize(int FontSize)
{
    CONSOLE_FONT_INFOEX info = { 0 };

    GetCurrentConsoleFontEx(hout, FALSE, &info);

    info.cbSize = sizeof(info);
    info.dwFontSize.Y = FontSize;

    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
}
void UI::setFont(std::string font) {
    CONSOLE_FONT_INFOEX info = { 0 };

    GetCurrentConsoleFontEx(hout, FALSE, &info);

    COORD fntSize = GetConsoleFontSize(hout, info.nFont);

    info.cbSize = sizeof(info);
    info.dwFontSize.X = fntSize.X;
    info.dwFontSize.Y = fntSize.Y;

    std::wstring str = to_wstring(font);
    lstrcpyW(info.FaceName, str.c_str());

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
    fwrite(&tlCorner, 1, 1, stdout);
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; gridL++; }
        if (i < columns - 1) {
            fwrite(&tGrid, 1, 1, stdout);
        }
    }
    fwrite(&trCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Rows
    cursor(pos.X, pos.Y);
    for (int i = 0; i < rows; i++) {
        fwrite(&vLine, 1, 1, stdout);
        fwrite(" ", 1, 1, stdout);
        for (int j = 0; j < columns; j++) { 
            fwrite(items[itemCount].c_str(), items[itemCount].size(), 1, stdout); // Print The Next item
            for (int k = items[itemCount].size(); k <= longest[0 + j]; k++) { // Space the grid square
                fwrite(" ", 1, 1, stdout);
            }
            fwrite(&vLine, 1, 1, stdout); // close the grid square
            fwrite(" ", 1, 1, stdout);
            itemCount++;
        }
        fwrite("\n", 1, 1, stdout);
        pos.Y++;
        cursor(pos.X, pos.Y);
        if (i < rows - 1) { // Print the next line into between rows
            fwrite(&lGrid, 1, 1, stdout);
            for (int i = 0; i < columns; i++) {
                for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; gridL++; }
                if (i < columns - 1) {
                    fwrite(&cGrid, 1, 1, stdout);
                }
            }
            fwrite(&rGrid, 1, 1, stdout);
            fwrite("\n", 1, 1, stdout);
        }
        pos.Y++;
        cursor(pos.X, pos.Y);
    }
    pos.Y--;

    // Output Bottom of the grid
    cursor(pos.X, pos.Y);
    fwrite(&blCorner, 1, 1, stdout);
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; }
        if (i < columns - 1) {
            fwrite(&bGrid, 1, 1, stdout);
        }
    }
    fwrite(&brCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);

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
                    fwrite(" ", 1, 1, stdout);
                }
                else {
                    fwrite(&text[k], 1, 1, stdout);
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
        fwrite(&tlCorner, 1, 1, stdout);
        for (int i = 0; i < wrap + 2; i++) {
            fwrite(&hLine, 1, 1, stdout);
        }
        fwrite(&trCorner, 1, 1, stdout);
        fwrite("\n", 1, 1, stdout);
        pos.Y++;

        // Output Wrapped Text
        for (int i = 0; i < text.size(); i += wrap) {
            cursor(pos.X, pos.Y);
            fwrite(&vLine, 1, 1, stdout);
            fwrite(" ", 1, 1, stdout);
            for (int k = place; k < (place + wrap); k++) {
                if (k >= text.size()) {
                    fwrite(" ", 1, 1, stdout);
                }
                else {
                    fwrite(&text[k], 1, 1, stdout);
                }
            }
            fwrite(" ", 1, 1, stdout);
            fwrite(&vLine, 1, 1, stdout);
            place += wrap;
            pos.Y++;
            cursor(pos.X, pos.Y);
        }

        cursor(pos.X, pos.Y);
        // Output Bottom Border
        fwrite(&blCorner, 1, 1, stdout);
        for (int i = 0; i < wrap + 2; i++) {
            fwrite(&hLine, 1, 1, stdout);
        }
        fwrite(&brCorner, 1, 1, stdout);
        fwrite("\n", 1, 1, stdout);
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
    fwrite(&tlCorner, 1, 1, stdout);
    for (int i = 0; i < longest + 3; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&trCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Title
    cursor(pos.X, pos.Y);
    fwrite(&vLine, 1, 1, stdout);
    fwrite(" ", 1, 1, stdout);
    fwrite(title.c_str(), title.size(), 1, stdout);

    for (int i = title.size(); i < longest + 2; i++) {
        fwrite(" ", 1, 1, stdout);
    }

    fwrite(&vLine, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;
    cursor(pos.X, pos.Y);
    fwrite(&lGrid, 1, 1, stdout);

    for (int i = 0; i < longest + 3; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }

    fwrite(&rGrid, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X, pos.Y);

        fwrite(&vLine, 1, 1, stdout); // Print item
        fwrite(" ", 1, 1, stdout);
        fwrite(items[i].c_str(), items[i].size(), 1, stdout);

        for (int j = items[i].size(); j < longest + 2; j++) { // Format size
            fwrite(" ", 1, 1, stdout);
        }

        fwrite(&vLine, 1, 1, stdout); // End line
        fwrite("\n", 1, 1, stdout);
        pos.Y++;
        cursor(pos.X, pos.Y);

    }

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    fwrite(&blCorner , 1, 1, stdout);
    for (int i = 0; i < longest + 3; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&brCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
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
void UI::editFile(std::string filepath) {
    //Vars
    std::vector<std::string> lines;
    std::string text;
    std::ifstream file;
    std::ofstream out;
    int longest;
    char vls[2] = { vLine, '\n' };
    COORD pos = { 0,1 };
    COORD screenMax = getWindowSize();
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    SMALL_RECT srctScrollRect, srctClipRect;
    CHAR_INFO chiFill;
    COORD coordDest;

    // Read file into vector
    file.open(filepath);
    if (!file.is_open()) {
        return;
    }
    lines.push_back("");
    while (getline(file, text)) {
        lines.push_back(text);
    }
    file.close();

    if (lines.size() == 1) {
        lines.push_back("");
    }

    // Output file
    cursor(pos);
    for (int i = 1; i < lines.size(); i++) {
        fwrite(lines[i].c_str(), lines[i].size(), 1, stdout);
        fwrite("\n", 1, 1, stdout);
    }

    // Read keyboard input
    INPUT_RECORD InputRecord;
    DWORD Events;
    cursor(0, 0);
    fwrite("| Save   Exit | (Hit Esc to enter the menu)", 43, 1, stdout);
    cursor(pos);
    while (1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if (InputRecord.EventType == KEY_EVENT) { 
            if (InputRecord.Event.KeyEvent.bKeyDown) {
                if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
                {
                    if (pos.X != 0) {
                        pos.X--;
                        cursor(pos);
                    }
                    else if (pos.Y > 1) {
                        pos.Y--;
                        pos.X = lines[pos.Y].size();
                        cursor(pos);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP)
                {
                    if (pos.Y > 1) {
                        pos.Y--;
                        if (pos.X > lines[pos.Y].size()) {
                            pos.X = lines[pos.Y].size();
                        }
                        cursor(pos);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
                {
                    if (pos.X < lines[pos.Y].size() && pos.Y != lines.size() - 1) {
                        pos.X++;
                        cursor(pos);
                    }
                    else {
                        pos.X = 0;
                        pos.Y++;
                        cursor(pos);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
                {
                    if(pos.Y != lines.size() - 1){
                        pos.Y++;
                        if (pos.X > lines[pos.Y].size()) {
                            pos.X = lines[pos.Y].size();
                        }
                        cursor(pos);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    //scrollConsoleBuffer(0, 1, screenMax.X, screenMax.Y, 0, 1);
                    cursor(0, 0);
                    fwrite("| ", 2, 1, stdout);
                    SetConsoleTextAttribute(hout, 11);
                    fwrite("Save", 4, 1, stdout);
                    SetConsoleTextAttribute(hout, 15);
                    fwrite("   Exit", 7, 1, stdout);
                    fwrite(" |                             ", 31, 1, stdout);
                    cursor(15, 0);
                    int curPos = 0;
                    while (1) {
                        ReadConsoleInput(hin, &InputRecord, 1, &Events);
                        if (InputRecord.EventType == KEY_EVENT) {
                            if (InputRecord.Event.KeyEvent.bKeyDown) {
                                if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
                                    curPos = 0;
                                    cursor(0, 0);
                                    fwrite("| ", 2, 1, stdout);
                                    SetConsoleTextAttribute(hout, 11);
                                    fwrite("Save", 4, 1, stdout);
                                    SetConsoleTextAttribute(hout, 15);
                                    fwrite("   Exit", 7, 1, stdout);
                                    fwrite(" |", 2, 1, stdout);
                                }
                                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
                                    curPos = 1;
                                    cursor(0, 0);
                                    SetConsoleTextAttribute(hout, 15);
                                    fwrite("| ", 2, 1, stdout);
                                    fwrite("Save   ", 7, 1, stdout);
                                    SetConsoleTextAttribute(hout, 11);
                                    fwrite("Exit", 4, 1, stdout);
                                    SetConsoleTextAttribute(hout, 15);
                                    fwrite(" |", 2, 1, stdout);
                                }
                                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                                    if (curPos == 0) {
                                        out.open(filepath);
                                        for (int i = 1; i < lines.size() - 1; i++) {
                                            out << lines[i] << "\n";
                                        }
                                        out << lines[lines.size() - 1];
                                        out.close();
                                        //scrollConsoleBuffer(0, 0, screenMax.X, screenMax.Y, 0, -1);
                                        cursor(0, 0);
                                        fwrite("| Save   Exit |", 15, 1, stdout);
                                        cursor(pos);
                                        break;
                                    }
                                    else {
                                        break;
                                    }
                                }
                                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                                    //scrollConsoleBuffer(0, 0, screenMax.X, screenMax.Y, 0, -1);
                                    cursor(0, 0);
                                    fwrite("| Save   Exit |", 15, 1, stdout);
                                    cursor(pos);
                                    break;
                                }
                            }
                        }
                    }
                    if (curPos == 1) {
                        break;
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                    scrollConsoleBuffer(0, pos.Y+1, screenMax.X, screenMax.Y, 0, pos.Y+2);

                    if (pos.X >= lines[pos.Y].size()) {
                        pos.Y++;
                        pos.X = 0;
                        cursor(pos);
                        lines.insert(lines.begin() + pos.Y,"");
                    }
                    else {
                        std::string split = lines[pos.Y].substr(pos.X, lines[pos.Y].size());
                        for (int i = 0; i < split.size(); i++) {
                            fwrite(" ", 1, 1, stdout);
                        }
                        lines[pos.Y].erase(pos.X, lines[pos.Y].size());
                        pos.Y++;
                        pos.X = 0;
                        lines.insert(lines.begin() + pos.Y, split);
                        cursor(pos);
                        fwrite(lines[pos.Y].c_str(), lines[pos.Y].size(), 1, stdout);
                        cursor(pos);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_SHIFT || InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_PRIOR || InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_NEXT || InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_MENU || InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_CONTROL) {

                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_BACK) {
                    if (pos.X == 0 && pos.Y != 1) {
                        if (lines[pos.Y].size() != 0) {
                            lines[pos.Y - 1].erase(lines[pos.Y - 1].begin() + lines[pos.Y - 1].size() - 1);
                            pos.X = lines[pos.Y - 1].size();
                            lines[pos.Y - 1].append(lines[pos.Y]);
                            lines.erase(lines.begin() + (pos.Y));
                            scrollConsoleBuffer(0, pos.Y, screenMax.X, screenMax.Y, 0, pos.Y - 1);
                            pos.Y--;
                            cursor(0, pos.Y);
                            fwrite(lines[pos.Y].c_str(), lines[pos.Y].size(), 1, stdout);
                            cursor(pos);
                        }
                        else {
                            lines.erase(lines.begin() + pos.Y);
                            pos.Y--;
                            pos.X = lines[pos.Y].size();
                            cursor(pos);
                        }
                    }
                    else {
                        lines[pos.Y].erase(lines[pos.Y].begin() + pos.X-1);
                        scrollConsoleBuffer(pos.X-1, pos.Y, lines[pos.Y].size(), pos.Y, pos.X - 2, pos.Y);
                        pos.X--;
                        cursor(pos);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DELETE) {
                    if (pos.X == 0) {

                    }
                    else {
                        lines[pos.Y].erase(lines[pos.Y].begin() + pos.X);
                        scrollConsoleBuffer(pos.X, pos.Y, lines[pos.Y].size(), pos.Y, pos.X - 1, pos.Y);
                    }
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_HOME) {
                    cursor(0, pos.Y);
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_END) {
                    cursor(lines[pos.Y].size(), pos.Y);
                }
                else if (InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_TAB) {
                    lines[pos.Y].insert(pos.X, (std::string)"    ");
                    pos.X = pos.X + 4;
                    cursor(0, pos.Y);
                    fwrite(lines[pos.Y].c_str(), lines[pos.Y].size(), 1, stdout);
                    cursor(pos);
                }
                else {
                    pos.X++;
                    if (pos.X >= lines[pos.Y].size()) {
                        lines[pos.Y].append(&InputRecord.Event.KeyEvent.uChar.AsciiChar);
                        fwrite(&InputRecord.Event.KeyEvent.uChar, 1, 1, stdout);
                    }
                    else if (lines[pos.Y].size() == 0) {
                        lines[pos.Y] = &InputRecord.Event.KeyEvent.uChar.AsciiChar;
                        fwrite(&InputRecord.Event.KeyEvent.uChar, 1, 1, stdout);
                    }
                    else {
                        lines[pos.Y].insert(lines[pos.Y].begin() + pos.X - 1, InputRecord.Event.KeyEvent.uChar.AsciiChar);
                        cursor(0, pos.Y);
                        fwrite(lines[pos.Y].c_str(), lines[pos.Y].size(), 1, stdout);
                    }
                    cursor(pos);
                }
            }

        }
    }

}

//~~ Menus ~~//
int UI::choiceMenu(COORD pos, std::string title, const char* choice, ...) {
    // Vars
    std::string pass;
    std::vector<std::string> items;
    int longest;
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
    fwrite(&tlCorner, 1, 1, stdout);
    for (int i = 0; i < longest + 6; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&trCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Title
    cursor(pos.X, pos.Y);
    fwrite(&vLine, 1, 1, stdout);
    fwrite(" ", 1, 1, stdout);
    fwrite(title.c_str(), title.size(), 1, stdout);
    for (int i = title.size(); i < longest + 5; i++) {
        fwrite(" ", 1, 1, stdout);
    }
    fwrite(&vLine, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);

    pos.Y++;
    cursor(pos.X, pos.Y);
    fwrite(&lGrid, 1, 1, stdout);
    for (int i = 0; i < longest + 6; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&rGrid, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X, pos.Y);
        fwrite(&vLine, 1, 1, stdout);
        fwrite(" ", 1, 1, stdout);
        fwrite(items[i].c_str(), items[i].size(), 1, stdout);
        for (int j = items[i].size(); j < longest + 2; j++) {
            fwrite(" ", 1, 1, stdout);
        }
        std::cout << "( )" << vLine << std::endl;
        fwrite("( )", 3, 1, stdout);
        fwrite(&vLine, 1, 1, stdout);
        fwrite("\n", 1, 1, stdout);
        pos.Y++;
        cursor(pos.X, pos.Y);
        
    }

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    fwrite(&blCorner, 1, 1, stdout);
    for (int i = 0; i < longest + 6; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&brCorner, 1, 1, stdout);


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
                fwrite(std::to_string(menupos).c_str(), 1, 1, stdout);
            }
            else {
                fwrite(" ", 1, 1, stdout);
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
    title = title + ":";

    // Output the Top of the Menu
    cursor(pos.X, pos.Y);
    fwrite(&tlCorner, 1, 1, stdout);
    for (int i = 0; i < title.size() + 4; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&trCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output center
    cursor(pos.X, pos.Y);
    fwrite(&vLine, 1, 1, stdout);
    fwrite(" ", 1, 1, stdout);
    fwrite(title.c_str(), title.size(), 1, stdout);
    fwrite("   ", 3, 1, stdout);
    fwrite(&vLine, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    fwrite(&blCorner, 1, 1, stdout);
    for (int i = 0; i < title.size() + 4; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&brCorner, 1, 1, stdout);
    pos.Y++;
    cursor(pos.X, pos.Y);
    fwrite("> ", 2, 1, stdout);
    //Update Border
    //std::cin.ignore();
    char buffer[2048];
    fgets(buffer, sizeof(buffer), stdin);
    std::string out = buffer;
    out.erase(out.begin() + out.size() - 1);
    return out;
}
std::vector<std::string> UI::loginMenu(COORD pos, std::string title, const char* choice, ...) {
    // Vars
    std::string pass;
    std::vector<std::string> items;
    std::vector<std::string> output;
    int longest;

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

    cursor(pos.X, pos.Y);
    //fwrite(&lHalf, 1, 1, stdout);
    fwrite(title.c_str(), title.size(), 1, stdout);
    fwrite("\n ", 1, 1, stdout);

    for (int i = 0; i < items.size(); i++) {
        fwrite(&lHalf, 1, 1, stdout);
        fwrite(items[i].c_str(), items[i].size(), 1, stdout);
        fwrite(":\n", 2, 1, stdout);
    }
    
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X+items[i].size() + 4, pos.Y+i+1);
        std::getline(std::cin, pass);
        output.push_back(pass);
        cursor(pos.X, pos.Y+i+1);
        SetConsoleTextAttribute(hout, 10);
        fwrite(&lHalf, 1, 1, stdout);
        fwrite(items[i].c_str(), items[i].size(), 1, stdout);
        fwrite(":", 1, 1, stdout);
        SetConsoleTextAttribute(hout, 15);
    }
    return output;
}
bool UI::boolMenu(COORD pos, std::string title) {
    // Vars
    bool choice = true;
    char ch = ' ';
    COORD loc;
    hideCursor();

    // Output Top Bar
    cursor(pos.X, pos.Y);
    fwrite(&tlCorner, 1, 1, stdout);
    for (int i = 0; i < title.size() + 2; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&trCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Center
    cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title << " " << vLine << std::endl;
    fwrite(&vLine + ' ', 2, 1, stdout);
    fwrite(title.c_str(), title.size(), 1, stdout);
    fwrite(' ' + &vLine + '\n', 3, 1, stdout);
    pos.Y++;
    cursor(pos.X, pos.Y);
    fwrite(&vLine, 1, 1, stdout);
    fwrite(" (*) Yes", 8, 1, stdout);

    for (int i = 0; i < title.size() - 8 + 2; i++) {
        fwrite(" ", 1, 1, stdout);
    }
    fwrite(&vLine, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;
    cursor(pos.X, pos.Y);
    fwrite(&vLine, 1, 1, stdout);
    fwrite(" ( ) No", 7, 1, stdout);
    for (int i = 0; i < title.size() - 7 + 2; i++) {
        fwrite(" ", 1, 1, stdout);
    }
    fwrite(&vLine, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Bottom Bar
    cursor(pos.X, pos.Y);
    fwrite(&blCorner, 1, 1, stdout);
    for (int i = 0; i < title.size() + 2; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&brCorner, 1, 1, stdout);

    while (1) {
        switch (choice) {
        case true:
            loc = getConsoleCursorPosition();
            cursor(loc.X - title.size() - 1, loc.Y - 2);
            fwrite("*", 1, 1, stdout);
            cursor(loc.X - title.size() - 1, loc.Y - 1);
            fwrite(" ", 1, 1, stdout);
            cursor(loc.X, loc.Y);
            break;
        case false:
            loc = getConsoleCursorPosition();
            cursor(loc.X - title.size() - 1, loc.Y - 2);
            fwrite(" ", 1, 1, stdout);
            cursor(loc.X - title.size() - 1, loc.Y - 1);
            fwrite("*", 1, 1, stdout);
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
    fwrite(">", 1, 1, stdout);

    while (1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if (InputRecord.EventType == KEY_EVENT) {
            if (InputRecord.Event.KeyEvent.bKeyDown) {
                in = InputRecord.Event.KeyEvent.wVirtualKeyCode;
                if (in == 0x08 && input.size() > 0) {
                    tPos = UI::getConsoleCursorPosition();
                    UI:cursor(tPos.X-1, tPos.Y);
                    fwrite(" ", 1, 1, stdout);
                    UI::cursor(pos.X + 1, pos.Y+1);
                    for (int i = 0; i < 8; i++) {
                        for (int k = 0; k < longest+6; k++) {
                            fwrite(" ", 1, 1, stdout);
                        }
                        fwrite("\n", 1, 1, stdout);
                    }
                    UI::cursor(pos.X + 1, pos.Y);
                    input.pop_back();
                    fwrite(input.c_str(), input.size(), 1, stdout);
                }
                else if (in == VK_DOWN && input.size() > 0) {
                    menupos = 1;
                    UI::cursor(smpos.X, smpos.Y+menupos);
                    fwrite(&cube, 1, 1, stdout);
                    while (menupos > 0) {
                        ReadConsoleInput(hin, &InputRecord, 1, &Events);
                        if (InputRecord.EventType == KEY_EVENT) {
                            if (InputRecord.Event.KeyEvent.bKeyDown) {
                                in = InputRecord.Event.KeyEvent.uChar.AsciiChar;
                                for (int i = 1; i < temp.size()+1; i++) {
                                    UI::cursor(smpos.X, smpos.Y + i);
                                    fwrite(" ", 1, 1, stdout);
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
                                fwrite(&cube, 1, 1, stdout);
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
                            fwrite(" ", 1, 1, stdout);
                        }
                        fwrite("\n", 1, 1, stdout);
                    }
                    UI::cursor(pos.X + 1, pos.Y);
                    input.push_back(in);
                    fwrite(input.c_str(), input.size(), 1, stdout);
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
            fwrite(&tlCorner, 1, 1, stdout);
            for (int i = 0; i < longest + 3; i++) {
                fwrite(&hLine, 1, 1, stdout);
            }
            fwrite(&trCorner, 1, 1, stdout);
            fwrite("\n", 1, 1, stdout);
            mPos.Y++;

            // Output Choices
            for (int i = 0; i < temp.size(); i++) {
                cursor(mPos.X, mPos.Y);
                fwrite(&vLine, 1, 1, stdout);
                fwrite(" ", 1, 1, stdout);
                fwrite(temp[i].c_str(), temp[i].size(), 1, stdout);
                for (int j = temp[i].size(); j < longest + 2; j++) {
                    fwrite(" ", 1, 1, stdout);
                }
                fwrite(&vLine, 1, 1, stdout);
                fwrite("\n", 1, 1, stdout);
                mPos.Y++;
                cursor(mPos.X, mPos.Y);

            }

            // Output the Bottom of the Menu
            cursor(mPos.X, mPos.Y);
            fwrite(&blCorner, 1, 1, stdout);
            for (int i = 0; i < longest + 3; i++) {
                fwrite(&hLine, 1, 1, stdout);
            }
            fwrite(&brCorner, 1, 1, stdout);
            UI::cursor(tPos.X, tPos.Y);
        }
    }
}

//~~ Progress Bars ~~//
void UI::ProgressBar::set_progress(float value) {
    progress_ = value;
}
void UI::ProgressBar::set_bar_width(size_t width) {
    bar_width_ = width;
}
void UI::ProgressBar::fill_bar_progress_with(const char& ch) {
    fill_ = ch;
}
void UI::ProgressBar::fill_bar_remainder_with(const char& ch) {
    remainder_ = ch;
}
void UI::ProgressBar::set_status_text(const std::string& status) {
    status_text_ = status;
}
void UI::ProgressBar::update(COORD pos, float value) {
    cursor(pos.X, pos.Y);
    set_progress(value);
    write_progress(pos);
}
void UI::ProgressBar::write_progress(COORD pos) {

    // No need to write once progress is 100%
    if (progress_ > 100.0f) return;

    // Move cursor to the first position on the same line and flush 
    cursor(pos.X, pos.Y);

    // Start bar
    fwrite("[", 1, 1, stdout);

    const auto completed = static_cast<size_t>(progress_ * static_cast<float>(bar_width_) / 100.0);
    for (size_t i = 0; i < bar_width_; ++i) {
        if (i <= completed)
            fwrite(fill_.c_str(), 1, 1, stdout);
        else
            fwrite(remainder_.c_str(), 1, 1, stdout);
    }

    // End bar
    fwrite("]", 1, 1, stdout);

    // Write progress percentage
    std::string percent = std::to_string(std::min(static_cast<size_t>(progress_), size_t(100)));
    fwrite(" ", 1, 1, stdout);
    fwrite(percent.c_str(), percent.size(), 1, stdout);
    fwrite("%", 1, 1, stdout);

    // Write status text
    fwrite(" ", 1, 1, stdout);
    fwrite(status_text_.c_str(), status_text_.size(), 1, stdout);
}

//~~ Mouse Handling ~~//
bool mouseEnabled = false;
void UI::enableMouseHandling() {
    SetConsoleMode(hin, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    mouseEnabled = true;
}
void UI::disabledMouseHandling() {
    SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
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
            fwrite(text.c_str(), text.size(), 1, stdout);
        }
        else {
            cursor(pos);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            fwrite(text.c_str(), text.size(), 1, stdout);
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
    fwrite(&tlCorner, 1, 1, stdout);
    for (int i = 0; i < longest + 6; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&trCorner, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Title
    cursor(pos.X, pos.Y);
    fwrite(&vLine, 1, 1, stdout);
    fwrite(" ", 1, 1, stdout);
    fwrite(title.c_str(), title.size(), 1, stdout);
    for (int i = title.size(); i < longest + 5; i++) {
        fwrite(" ", 1, 1, stdout);
    }
    fwrite(&vLine, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);

    pos.Y++;
    cursor(pos.X, pos.Y);
    fwrite(&lGrid, 1, 1, stdout);
    for (int i = 0; i < longest + 6; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&rGrid, 1, 1, stdout);
    fwrite("\n", 1, 1, stdout);
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        cursor(pos.X, pos.Y);
        fwrite(&vLine, 1, 1, stdout);
        fwrite(" ", 1, 1, stdout);
        fwrite(items[i].c_str(), items[i].size(), 1, stdout);
        for (int j = items[i].size(); j < longest + 2; j++) {
            fwrite(" ", 1, 1, stdout);
        }
        fwrite("   ", 3, 1, stdout);
        fwrite(&vLine, 1, 1, stdout);
        fwrite("\n", 1, 1, stdout);
        pos.Y++;
        cursor(pos.X, pos.Y);

    }

    // Output the Bottom of the Menu
    cursor(pos.X, pos.Y);
    fwrite(&blCorner, 1, 1, stdout);
    for (int i = 0; i < longest + 6; i++) {
        fwrite(&hLine, 1, 1, stdout);
    }
    fwrite(&brCorner, 1, 1, stdout);


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
            fwrite(items[i].c_str(), items[i].size(), 1, stdout);
        }
        for (int i = 0; i < points.size(); i++) {
            if (p.X >= points[i].X - longest - 2 && p.X <= points[i].X && p.Y == points[i].Y) {
                UI::cursor(points[i].X - longest - 3, points[i].Y);
                SetConsoleTextAttribute(hout, 11);
                fwrite(items[i].c_str(), items[i].size(), 1, stdout);
            }
        }
        if (InputRecord.EventType == MOUSE_EVENT) {
            if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                for (int i = 0; i < points.size(); i++) {
                    if (p.X >= points[i].X - longest - 2 && p.X <= points[i].X && p.Y == points[i].Y) {
                        UI::cursor(points[i].X - longest - 4, points[i].Y);
                        SetConsoleTextAttribute(hout, 187);
                        fwrite(" ", 1, 1, stdout);
                        fwrite(items[i].c_str(), items[i].size(), 1, stdout);
                        for (int k = items[i].size(); k < longest + 2; k++) {
                            fwrite(" ", 1, 1, stdout);
                        }
                        fwrite("   ", 3, 1, stdout);
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
