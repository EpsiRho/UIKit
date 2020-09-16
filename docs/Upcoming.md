# Upcoming Features <!-- {docsify-ignore} -->
## Settings
#### Info
> Give the developer the ability to change things such as:<br>
> * Color highlighting (highlights current menu option with dev choice)<br> 
> * Turn on and off the Borders around menus
#### Syntax Prototype
`UI::Setings.highlight = 10;`

## Multi Progress Bar Class
#### Info
> Will offer support for multiple progress bars recivcing updates at a time


## Screenshot
#### Info 
> Take a "Screenshot" of every character on the terminal window and send it to a string / file

#### Syntax Prototype
`std::string out = UI::Screenshot();`

## Refresh 
#### Info
> Clears/Replaces a set area of the screen

#### Syntax Prototpye
`UI::Refresh(int x1, int y1, int x2, int y2, const char* ch);`<br>
`UI::Refresh(int x1, int y1, int x2, int y2, std::string str);`

## Window Handling
#### Info
> Allows you to change the height / width and if the window is show / hiddem / fullscreen

#### Syntax Prototype
`UI::windowHeight(int height);`<br>
`UI::windowWidth(int width);`<br>
`UI::windowMode(std::string);`<br>

## Font Handling
#### Info
> Allows you to change the font, font size, etc

#### Syntax Prototype
`UI::FontSize(int size);`<br>
`UI::Font(std::string);`