## List
#### Info
> Displays a list of items
#### Syntax
`list(COORD pos, std::string title, const char* item, NULL);`

* *pos* - a COORD with the x and y position for the window to be placed
* *title* - The string to be placed in the title box
* *item* - Takes any remaining strings and displays them as the list
* *NULL* - Tells the command to stop looking for string arguments

#### Example
```C++
UI::list(pos, "To-Do", "Fix Code", "Sleep", "Sleep but again", "Sleep but this time on the couch", NULL);
```

#### Output
```
┌───────────────────────────────────┐
│ To-Do                             │
├───────────────────────────────────┤
│ Fix Code                          │
│ Sleep                             │
│ Sleep but again                   │
│ Sleep but this time on the couch  │
└───────────────────────────────────┘
```