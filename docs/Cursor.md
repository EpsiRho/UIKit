# Cursor Handling <!-- {docsify-ignore} -->
UIKit Provides an easy way to manage the console's cursor
## Cursor Movement
#### Info
> Moves the cursor to the Specified X, Y
#### Syntax
`cursor(int x, int y);`<br>
*X* - integer that represents the x<br>
*Y* - integer that represents the y

`cursor(COORD destCoord)`<br>
*destCoord* - COORD Variable that contains x and y to the point desired

#### Example
```C++
UI::cursor(10, 11);
UI::color("*[10,11]", 15);
```

## Cursor Position
#### Info
> Returns a COORD Variable with the current x and y of the cursor
#### Syntax
`GetConsoleCursorPosition();`

#### Example
```C++
COORD home = UI::GetConsoleCursorPosition();
UI::cursor(0,5);
std::cout << "*";
UI::cursor(home);
````

## Cursor Visibility
#### Info
> Hides or Shows the Cursor
#### Syntax
`hideCursor();` <br>
`showCursor();`

#### Example
```C++
UI::hideCursor();
UI::cursor(20, 5);
std::cout << "hi";
UI::cursor(0,0);
UI::showCursor();
```