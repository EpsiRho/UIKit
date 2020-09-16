## Search Bar <!-- {docsify-ignore} -->
#### Info
> Allows the use to search through a vector of strings<br>
> returns the string the user selected<br>
> User can type and the box below will show the top 6 results<br>
> by hitting the down arrow, the user can move to selection mode, where they can use the arrow keys to select one of the results
#### Syntax
`searchBar(COORD pos, std::vector<std::string> list)`

* *pos* - a COORD with the x and y position for the window to be placed
* *list* - A vector of strings for the user to search through

#### Example
```C++
std::string str_input = UI::searchBar(ps, list);
```

#### Output
```
// Users sees an arrow untill they stop
>

// after typing..
>NIN
┌──────────────────┐
│ NINTENDO DS      │
│ NINTENDO 3DS     │
│ NINTENDO WII     │
│ NINTENDO SWITCH  │
└──────────────────┘
```