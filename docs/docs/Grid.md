## Grid <!-- {docsify-ignore} -->
#### Info
> Displays a Custom Grid<br>
> Grid Cells MUST be terminated with NULL
#### Syntax
`grid(COORD pos, int columns, int rows, const char* arg, NULL);`

* *pos* - a COORD with the x and y postion for the window to be placed
* *columns* - The Number of Columns in the grid
* *rows* - The Number of Rows in the grid
* *arg* - Takes as many strings as inputed and Puts them into the grid. **Every grid space must have a corisponding string**, ("" to put an empty space)
* *NULL* - Tells the command to stop looking for string arguments

#### Example
```C++
UI::grid(pos, 3, 4, "Name", "Rank", "Date Started",
						   "Jeremy", "Worker", "04/23/20",
						   "Zack", "Captain", "06/11/17",
						   "Noah", "", "TBD", NULL);
```

#### Output
```
┌────────┬─────────┬──────────────┐
│ Name   │ Rank    │ Date Started │
├────────┼─────────┼──────────────┤
│ Jeremy │ Worker  │ 04/23/20     │
├────────┼─────────┼──────────────┤
│ Zack   │ Captain │ 06/11/17     │
├────────┼─────────┼──────────────┤
│ Noah   │         │ TBD          │
└────────┴─────────┴──────────────┘
```
