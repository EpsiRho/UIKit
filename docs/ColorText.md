# Color <!-- {docsify-ignore} -->
## Colored Text
#### Info
> Using Color() you can output a string in a desired color
#### Syntax
`color(string text, int clr);`

* *text* - The string to be colored

* *clr* - The integer ID to a color

#### Example
```C++
UI::color("This text will be light blue", 11);
```

## Default Color
#### Info
> Instead of just one string, DefaultColor() Sets the base color for the entire console window
#### Syntax
`defaultColor(int clr);`

*clr* - The integer ID to a color

#### Example
```C++
UI::defaultColor(120);
```