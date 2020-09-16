# Cursor Handling <!-- {docsify-ignore} -->
UIKit Provides an easy way to manage the console's cursor
## Cursor Movement
#### Info
> Moves the cursor to the Specified X, Y
#### Syntax
`Cursor(int x, int y);`<br>
*X* - integer that represents the x<br>
*Y* - integer that represents the y

`Cursor(COORD destCoord)`<br>
*destCoord* - COORD Variable that contains x and y to the point desired

#### Example
```C++
UI::Cursor(10, 11);
UI::Color("*[10,11]", 15);
```

## Cursor Position
#### Info
> Returns a COORD Variable with the current x and y of the cursor
#### Syntax
`GetConsoleCursorPosition();`

#### Example
```C++
COORD home = UI::GetConsoleCursorPosition();
UI::Cursor(0,5);
std::cout << "*";
UI::Cursor(home);
````

## Cursor Visibility
#### Info
> Hides or Shows the Cursor
#### Syntax
`HideCursor();` <br>
`ShowCursor();`

#### Example
```C++
UI::HideCursor();
UI::Cursor(20, 5);
std::cout << "hi";
UI::Cursor(0,0);
UI::ShowCursor();
```