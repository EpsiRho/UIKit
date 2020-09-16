# Experimental Functions <!-- {docsify-ignore} -->

## Choice Menu with Mouse Support
#### Info
> #### **IMPORTANT: While this function is implemented and works, it causes input with cin to stop working.**<br>
> Works in the same way as a [Choice Menu](ChoiceMenu)<br>
> Turns off the windows terminal Quick Edit mode(so no selection of text is availible while the function runs)<br>
> Returns the integer of the choice the user clicked on
#### Syntax
` mouseChoiceMenu(COORD pos, std::string title, const char* choice, NULL);`

* *pos* - a COORD with the x and y position for the window to be placed
* *title* - The string to be placed in the title box
* *choice* - Takes any remaining strings and places them in choice boxes
* *NULL* - Tells the command to stop looking for string arguments

#### Example
```C++
usr_input = UI::mouseChoiceMenu(pos, "Mouse Test", "Check 1", "Check 2", "Check 3", NULL);
```

#### Output
```
┌─────────────┐
│ Mouse Test  │
├─────────────┤
│ Check 1   █▌│
│ Check 2   █▌│
│ Check 3   █▌│
└─────────────┘
```

### Known Issues and Upcoming Changes
#### Bugs
* cin input stops working after function completes

#### Upcoming Changes
* Click Hitbox spans over the whole string
* Settings Integration