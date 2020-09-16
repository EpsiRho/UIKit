## Choice Menu <!-- {docsify-ignore} -->
#### Info
> Outputs a Menu of choices that the user can select by number<br>
> Operated with up and down arrow keys <br>
> Returns the integer of the menu index chosen by the user.<br>
> Choices MUST be terminated with NULL
#### Syntax
`choiceMenu(COORD pos, string title, const char* choice, NULL);`

* *pos* - a COORD with the x and y position for the window to be placed
* *title* - The string to be placed in the title box
* *choice* - Takes any remaining strings and places them in choice boxes
* *NULL* - Tells the command to stop looking for string arguments

#### Example
```C++
int usr_input = UI::choiceMenu(pos, "Test Menu:", "execute", "help", "connect", "disconnect", NULL);
```

#### Output
```
┌───────────────────┐
│ Test Menu:        │
├───────────────────┤
│ execute        (1)│
│ help           ( )│
│ connect        ( )│
│ disconnect     ( )│
└───────────────────┘
```