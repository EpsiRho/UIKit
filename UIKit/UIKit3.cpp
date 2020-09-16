#include "UIKit3.h"

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


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void UI::ClearScreen()
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

COORD UI::GetConsoleCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
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

void UI::Grid(COORD pos, int columns, int rows, const char* arg, ...) {
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
    Cursor(pos.X, pos.Y);
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
    Cursor(pos.X, pos.Y);
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
        Cursor(pos.X, pos.Y);
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
        Cursor(pos.X, pos.Y);
    }
    pos.Y--;
    // Output Bottom of the grid
    Cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < longest[i] + 2; j++) { std::cout << hLine; }
        if (i < columns - 1) {
            std::cout << bGrid;
        }
    }
    std::cout << brCorner << std::endl;

}

void UI::Wrapper(COORD pos, std::string text, int wrap, int border) {
    // Vars
    int place = 0;

    switch (border) {
    case 0: // Output without a border
        // Output Wrapped Text

        for (int i = 0; i < text.size(); i += wrap) {
            Cursor(pos.X, pos.Y);
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
            Cursor(pos.X, pos.Y);
        }
        break;
    case 1: // Output With a border
        // Output Top Border
        Cursor(pos.X, pos.Y);
        std::cout << tlCorner;
        for (int i = 0; i < wrap + 2; i++) {
            std::cout << hLine;
        }
        std::cout << trCorner << std::endl;
        pos.Y++;

        // Output Wrapped Text
        for (int i = 0; i < text.size(); i += wrap) {
            Cursor(pos.X, pos.Y);
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
            Cursor(pos.X, pos.Y);
        }

        Cursor(pos.X, pos.Y);
        // Output Bottom Border
        std::cout << blCorner;
        for (int i = 0; i < wrap + 2; i++) {
            std::cout << hLine;
        }
        std::cout << brCorner << std::endl;
        break;
    }
}

void UI::Color(std::string text, int clr) {
    SetConsoleTextAttribute(hConsole, clr);
    std::cout << text << std::endl;
    SetConsoleTextAttribute(hConsole, 7);
}

int UI::choiceMenu(COORD pos, std::string title, const char* choice, ...) {
    // Vars
    std::string pass;
    std::vector<std::string> items;
    int longest;
    int usr_input;
    COORD loc;
    char in = ' ';
    int menupos;
    HideCursor();
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

    // Output the Top of the Menu
    Cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Title
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title;
    for (int i = title.size(); i < longest + 5; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    Cursor(pos.X, pos.Y);
    std::cout << lGrid;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << rGrid << std::endl;
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        Cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[i];
        for (int j = items[i].size(); j < longest + 2; j++) {
            std::cout << " ";
        }
        std::cout << "( )" << vLine << std::endl;
        pos.Y++;
        Cursor(pos.X, pos.Y);
        
    }

    // Output the Bottom of the Menu
    Cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;


    // User input
    menupos = 1;
    loc = GetConsoleCursorPosition();
    COORD home = loc;
    while (in != '\r') {
        Cursor(loc.X - 3, loc.Y - items.size() - 1);
        home = GetConsoleCursorPosition();
        for (int i = 1; i <= items.size(); i++) {
            Cursor(home.X, home.Y + i );
            if (i == menupos) {
                std::cout << menupos;
            }
            else {
                std::cout << " ";
            }
            Cursor(loc.X, loc.Y);
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
    ShowCursor();
    return menupos;
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
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

    HideCursor();
    SetConsoleMode(hin, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

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

    // Output the Top of the Menu
    Cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Title
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title;
    for (int i = title.size(); i < longest + 5; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    Cursor(pos.X, pos.Y);
    std::cout << lGrid;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << rGrid << std::endl;
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        Cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[i];
        for (int j = items[i].size(); j < longest + 2; j++) {
            std::cout << " ";
        }
        std::cout << "  " << (char)221 << vLine << std::endl;
        pos.Y++;
        Cursor(pos.X, pos.Y);

    }

    // Output the Bottom of the Menu
    Cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < longest + 6; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;


    // User input
    menupos = 1;
    loc = GetConsoleCursorPosition();
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
            UI::Cursor(points[i].X, points[i].Y);
            SetConsoleTextAttribute(hConsole, 8);
            std::cout << sel << ptr;
        }
        for (int i = 0; i < points.size(); i++) {
            if (p.X == points[i].X && p.Y == points[i].Y || p.X == points[i].X+1 && p.Y == points[i].Y) {
                UI::Cursor(points[i].X, points[i].Y);
                SetConsoleTextAttribute(hConsole, 15);
                std::cout << sel << ptr;
            }
        }
        if (InputRecord.EventType == MOUSE_EVENT) {
            if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                for (int i = 0; i < points.size(); i++) {
                    if (p.X == points[i].X && p.Y == points[i].Y) {
                        UI::Cursor(p.X, p.Y);
                        std::cout << clk;
                        ShowCursor();
                        SetConsoleMode(hin, ENABLE_QUICK_EDIT_MODE | ENABLE_LINE_INPUT );
                        return i;
                    }
                }
            }
        }
    }

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
    Cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < title.size() + finished.size() + 4; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output center
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title << ":" << finished << "  " << vLine << std::endl;
    pos.Y++;

    // Output the Bottom of the Menu
    Cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < title.size() + finished.size() + 4; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;
    pos.Y++;
    Cursor(pos.X, pos.Y);
    std::cout << "> ";
    //Update Border
    std::cin.ignore();
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

    HideCursor();

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
        Cursor(pos.X, pos.Y);
        std::cout << tlCorner;
        for (int i = 0; i < items[a].size() + finished.size() + 4; i++) {
            std::cout << hLine;
        }
        std::cout << trCorner << std::endl;
        pos.Y++;

        // Output center
        Cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[a] << ": " << finished << " " << vLine << std::endl;
        pos.Y++;

        // Output the Bottom of the Menu
        Cursor(pos.X, pos.Y);
        std::cout << blCorner;
        for (int i = 0; i < items[a].size() + finished.size() + 4; i++) {
            std::cout << hLine;
        }
        std::cout << brCorner << std::endl;
        pos.Y++;

        // Update Menu Border
        while (in != '\r') {
            Cursor(pos.X, pos.Y);
            in = _getch();
            if (in == '\b' && finished.size() > 0) {
                finished.erase(finished.begin() + finished.size() - 1);
                origionLoc = GetConsoleCursorPosition();
                loc = origionLoc;
                Cursor(loc.X + (finished.size() + items[a].size()) + 5, loc.Y - 3);
                std::cout << hLine << trCorner << " " << "  ";
                loc = GetConsoleCursorPosition();
                Cursor(loc.X - finished.size() - 5, loc.Y + 1);
                std::cout << finished << " " << vLine << "     ";;
                loc = GetConsoleCursorPosition();
                Cursor(loc.X - 7, loc.Y + 1);
                std::cout << hLine << brCorner << " " << "  ";
                Cursor(origionLoc.X, origionLoc.Y);
            }
            else if(in != '\b' && in != '\r'){
                finished += in;
                origionLoc = GetConsoleCursorPosition();
                loc = origionLoc;
                Cursor(loc.X + (finished.size() + items[a].size()) + 3, loc.Y - 3);
                std::cout << hLine << hLine << hLine << trCorner;
                loc = GetConsoleCursorPosition();
                Cursor(loc.X - finished.size() - 2, loc.Y + 1);
                std::cout << finished << " " << vLine;
                loc = GetConsoleCursorPosition();
                Cursor(loc.X - 3, loc.Y + 1);
                std::cout << hLine << hLine << brCorner;
                Cursor(origionLoc.X, origionLoc.Y);
            }
        }
        //finished.erase(finished.begin() + finished.size() - 1);
        send.push_back(finished);
        in = ' ';
        finished = "";
    }
    ClearScreen();
    ShowCursor();
    return send;
}

bool UI::boolMenu(COORD pos, std::string title) {
    // Vars
    bool choice = true;
    char ch = ' ';
    COORD loc;
    HideCursor();
    //ClearScreen();

    // Output Top Bar
    Cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < title.size() + 2; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Center
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title << " " << vLine << std::endl;
    pos.Y++;
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << "(*) Yes"; 
    for (int i = 0; i < title.size() - 8 + 2; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << "( ) No";
    for (int i = 0; i < title.size() - 7 + 2; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;

    // Output Bottom Bar
    Cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < title.size() + 2; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;

    while (1) {
        switch (choice) {
        case true:
            loc = GetConsoleCursorPosition();
            Cursor(loc.X - title.size() - 1, loc.Y - 2);
            std::cout << "*";
            Cursor(loc.X - title.size() - 1, loc.Y - 1);
            std::cout << " ";
            Cursor(loc.X, loc.Y);
            break;
        case false:
            loc = GetConsoleCursorPosition();
            Cursor(loc.X - title.size() - 1, loc.Y - 2);
            std::cout << " ";
            Cursor(loc.X - title.size() - 1, loc.Y - 1);
            std::cout << "*";
            Cursor(loc.X, loc.Y);
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
    ShowCursor();
}

void UI::DefaultColor(int clr) {
    SetConsoleTextAttribute(hConsole, clr);
}

void UI::Cursor(int x, int y) {
    COORD destCoord;
    destCoord.Y = y;
    destCoord.X = x;
    SetConsoleCursorPosition(hConsole, destCoord);
}
void UI::Cursor(COORD destCoord) {
    SetConsoleCursorPosition(hConsole, destCoord);
}

void UI::HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void UI::ShowCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 15;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
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
    Cursor(pos.X, pos.Y);
    std::cout << tlCorner;
    for (int i = 0; i < longest + 3; i++) {
        std::cout << hLine;
    }
    std::cout << trCorner << std::endl;
    pos.Y++;

    // Output Title
    Cursor(pos.X, pos.Y);
    std::cout << vLine << " " << title;
    for (int i = title.size(); i < longest + 2; i++) {
        std::cout << " ";
    }
    std::cout << vLine << std::endl;
    pos.Y++;
    Cursor(pos.X, pos.Y);
    std::cout << lGrid;
    for (int i = 0; i < longest + 3; i++) {
        std::cout << hLine;
    }
    std::cout << rGrid << std::endl;
    pos.Y++;

    // Output Choices
    for (int i = 0; i < items.size(); i++) {
        Cursor(pos.X, pos.Y);
        std::cout << vLine << " " << items[i];
        for (int j = items[i].size(); j < longest + 2; j++) {
            std::cout << " ";
        }
        std::cout << vLine << std::endl;
        pos.Y++;
        Cursor(pos.X, pos.Y);

    }

    // Output the Bottom of the Menu
    Cursor(pos.X, pos.Y);
    std::cout << blCorner;
    for (int i = 0; i < longest + 3; i++) {
        std::cout << hLine;
    }
    std::cout << brCorner;


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

    UI::Cursor(pos.X, pos.Y);
    std::cout << ">";

    while (1) {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        if (InputRecord.EventType == KEY_EVENT) {
            if (InputRecord.Event.KeyEvent.bKeyDown) {
                in = InputRecord.Event.KeyEvent.wVirtualKeyCode;
                if (in == 0x08 && input.size() > 0) {
                    tPos = UI::GetConsoleCursorPosition();
                    UI:Cursor(tPos.X-1, tPos.Y);
                    std::cout << " ";
                    UI::Cursor(pos.X + 1, pos.Y+1);
                    for (int i = 0; i < 8; i++) {
                        for (int k = 0; k < longest+6; k++) {
                            std::cout << " ";
                        }
                        std::cout << "\n";
                    }
                    UI::Cursor(pos.X + 1, pos.Y);
                    input.pop_back();
                    std::cout << input;
                }
                else if (in == VK_DOWN && input.size() > 0) {
                    menupos = 1;
                    UI::Cursor(smpos.X, smpos.Y+menupos);
                    std::cout << (char)254;
                    while (menupos > 0) {
                        ReadConsoleInput(hin, &InputRecord, 1, &Events);
                        if (InputRecord.EventType == KEY_EVENT) {
                            if (InputRecord.Event.KeyEvent.bKeyDown) {
                                in = InputRecord.Event.KeyEvent.wVirtualKeyCode;
                                for (int i = 1; i < temp.size()+1; i++) {
                                    UI::Cursor(smpos.X, smpos.Y + i);
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
                                UI::Cursor(smpos.X, smpos.Y + menupos);
                                std::cout << (char)254;
                            }
                        }
                    }
                    UI::Cursor(tPos.X, tPos.Y);
                }
                else if (in == 0x0D) {
                    
                }
                else if(in != 0x08){
                    UI::Cursor(pos.X + 1, pos.Y+1);
                    for (int i = 0; i < 8; i++) {
                        for (int k = 0; k < longest+6; k++) {
                            std::cout << " ";
                        }
                        std::cout << "\n";
                    }
                    UI::Cursor(pos.X + 1, pos.Y);
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
            tPos = UI::GetConsoleCursorPosition();
            COORD mPos = pos;
            mPos.Y++;
            // Output the Top of the Menu
            Cursor(mPos.X, mPos.Y);
            std::cout << tlCorner;
            for (int i = 0; i < longest + 3; i++) {
                std::cout << hLine;
            }
            std::cout << trCorner << std::endl;
            mPos.Y++;

            // Output Choices
            for (int i = 0; i < temp.size(); i++) {
                Cursor(mPos.X, mPos.Y);
                std::cout << vLine << " " << temp[i];
                for (int j = temp[i].size(); j < longest + 2; j++) {
                    std::cout << " ";
                }
                std::cout << vLine << std::endl;
                mPos.Y++;
                Cursor(mPos.X, mPos.Y);

            }

            // Output the Bottom of the Menu
            Cursor(mPos.X, mPos.Y);
            std::cout << blCorner;
            for (int i = 0; i < longest + 3; i++) {
                std::cout << hLine;
            }
            std::cout << brCorner;
            UI::Cursor(tPos.X, tPos.Y);
        }
    }
}


// Progress Bar Class Define
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
    Cursor(pos.X, pos.Y);
    set_progress(value);
    write_progress(pos);
}

void UI::ProgressBar::write_progress(COORD pos) {
    std::ostream& os = std::cout;
    std::unique_lock lock{ mutex_ };

    // No need to write once progress is 100%
    if (progress_ > 100.0f) return;

    // Move cursor to the first position on the same line and flush 
    Cursor(pos.X, pos.Y);

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