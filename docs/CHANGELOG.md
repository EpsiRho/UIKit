# Changelog <!-- {docsify-ignore} -->
- - -

## Beta 1
### Additions
- ClearScreen: Fast screen clear
- Grid: Displays a grid
- Wrapper: wraps text
- Color: prints colored text
- Err: displays a flashing error text
- cMenu: displays a menu of choices
- tMenu: displays a menu with string input
- - - 

## Beta 2
### Additions
- pMenu: displays a pathed menu
- bMenu: displays a yes or no menu
- DefaultColor: sets the default console color
- Cursor: moves the console cursor
- ProgressBar: displays a custom progressbar
- Show/HideCursor: shows or hides the console cursor

- - -

## Beta 3
### Changes
- Syntax update for Grid, Wrapper, cMenu, tMenu, pMenu, and Progressbar to include `COORD pos` for positioning the menu on the screen
- Command names changed to be long form (`cMenu` -> `choiceMenu`)

### Additions
- list command

- - -

## Beta 4
### Additions
- [ClearPos](https://epsirho.github.io/UIKit/#/ClearPos)
- [Clipboard](https://epsirho.github.io/UIKit/#/Clipboard)
- [Font Handling](https://epsirho.github.io/UIKit/#/Font)
- [Mouse Handling](https://epsirho.github.io/UIKit/#/Mouse)
- [Refresh](https://epsirho.github.io/UIKit/#/refresh)
- [Window Handling](https://epsirho.github.io/UIKit/#/Window)

### Changes
- Syntax fixed to be consistant camelCase
- list made a seprate command from upcomming editList command
- mouseChoiceMenu Clicking and highlighting extended
- color command now has overloaded syntax ( `UI::color(int x, int y);` and `UI::color(COORD pos);` )

### Fixes
- mouseChoiceMenu breaking text input
- GetConsoleCursorPosition Not Working
- MouseChoiceMenu bugged when changing Y from 0
- Default Console Color not working
- Menu titles being larger than choices causes clipping issues
- Color not working after syntax change

- - -

## Beta 5
#### Additions
- [Login Menu](https://epsirho.github.io/UIKit/#/LoginMenu)
- [Edit File](https://epsirho.github.io/UIKit/#/editFile) `Incomplete`
- [Scroll Console Buffer](https://epsirho.github.io/UIKit/#/scrollConsole)

#### Removed
- pathMenu has been removed and replaced by the [Login Menu](https://epsirho.github.io/UIKit/#/LoginMenu).

#### Fixes
- Fixed Text Menu
- Fixed broken input after mouse input disable
- Text Menu Left '\n' in the returned string
- Fixed Progress Bar character errors after update to fwrite
- Cleaned up unneeded code.
- all std::cout removed and switched to fwrite

#### Docs
- [Progress Bar](https://epsirho.github.io/UIKit/#/Progress) docs now have info on set_status_text

### Fixes
- Remove the need for NULL at the end of ... args `Incomplete`

- - - 

## Beta 6 Release `Future Release`
### Additions
- Multiple progressbars
- Screenshot the console window and save it to a file

#### Syntax changes for:
- grid (Overload `const char* arg, ...` with `std::vector<std::string> args`) `Incomplete`
- list (Overload `const char* item, ...` with `std::vector<std::string> args`) `Incomplete`
- choiceMenu (Overload `const char* choice, ...` with `std::vector<std::string> args`) `Incomplete`
- loginMenu (Overload `const char* choice, ...` with `std::vector<std::string> args`) `Incomplete`
- searchBar (Overload `std::vector<std::string> args` with `const char* arg, ...` ) `Incomplete`
- mouseChoiceMenu (Overload `const char* choice, ...` with `std::vector<std::string> args`) `Incomplete`

#### Demo
- Demo Complete with commenting and examples for every function `Incomplete`

- - - 

## UIKit 1.0 Release `Future Release`
### Additions
- Clickable buttons

### Fixes
- Code Cleanup
- More detailed commenting
-

- - - 