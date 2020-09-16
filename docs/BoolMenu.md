## Boolean Menu <!-- {docsify-ignore} -->
 
#### Info
> Outputs a Menu that allows the user to select yes or no <br>
> Operated with up and down arrow keys <br>
> Returns a Boolen Value Chosen by the User
#### Syntax
`boolMenu(COORD pos, string _title_);`

* *pos* - a COORD with the x and y position for the window to be placed
* *title* - The string to be placed as the question for the user

#### Example
```C++
bmenu = UI::boolMenu(pos, "Do you accept the terms of service?");
if(bmenu == false){
    return 1;
}
```
#### Ouput
```
┌─────────────────────────────────────┐
│ Do you accept the terms of service? │
│ (*) Yes                             │
│ ( ) No                              │
└─────────────────────────────────────┘
```