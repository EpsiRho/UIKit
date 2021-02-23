# Mouse Handling <!-- {docsify-ignore} -->

## Enabling/Disabling Mouse Mode
> You can enable mouse handling with `enableMouseHandling();`<br>
> You can disable mouse handling with `disableMouseHandling();`

## Getting the current mouse position
> `getMousePos();` Returns a COORD with the current location of the mouse pointer

## Waiting for the user to click
> `waitForClick();` Will stop the program until the user clicks anywhere and the console window

## Clipboard Copy Button
#### Info
> This creates texts that highlights when a mouse moves over it<br>
> Upon user click, the text will be coppied the the clipboard<br>
> This function is infinte, and should **ONLY** be used in an seperate thread<br>
> It can be stopped with `clipboardEnd();`

#### Syntax
`void clipboardText(COORD pos, std::string text, std::string copy);`
* *pos* - a COORD with the x and y position for the text to be placed
* *text* - the text to be shown
* *copy* - the text to be added to the clipboard

#### Example
```
UI::enableMouseHandling();
UI::hideCursor();
COORD pos = { 10, 5 };
future<void> clip = async(&UI::clipboardText, pos, "Click on me to copy me!", "Never gonna give you up, Never gonna let you down");
Sleep(5000);
UI::clipboardEnd();
```

## Choice Menu with Mouse Support
#### Info
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
│ Check 1     │
│ Check 2     │
│ Check 3     │
└─────────────┘
```