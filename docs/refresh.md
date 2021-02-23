## Refresh <!-- {docsify-ignore} -->

#### Info
> Replaces a portion of the console with the supplied text<br>
> string must be the same size of the number of characters in the defined rectangle
#### Syntax
`refresh(int x1, int y1, int x2, int y2, std::string chars);`
* *x1* - the starting x 
* *y1* - the starting y
* *x2* - the ending x 
* *y2* - the edning y
#### Example
```C++
UI::color("Temporary block\nof random\ntexts", 12);
Sleep(1000);
UI::refresh(0, 0, 9, 1, "Permanent good bits");
```