# In the Process of being Re-Written
## Text Menu <!-- {docsify-ignore} -->
#### Info
> Displays a menu box that takes a string input from the user<br>
> Returns a string
#### Syntax
`textMenu(COORD pos, std::string title);`

* *pos* - a COORD with the x and y position for the window to be placed
* *title* - Title string to put in the menu box

#### Example
```C++
std::string str_input = UI::textMenu(pos, "Console Test Menu");
```

#### Output 
```
┌─────────────────────┐
│ Console Test Menu:  │
└─────────────────────┘
>
```