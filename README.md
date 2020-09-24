# UIKit
A c++ Library for easy, nice looking console GUIs

### [DOCUMENTATION](https://epsirho.github.io/UIKit/#/)

### [Demo Application](https://github.com/EpsiRho/UIKit/releases/tag/b-4.4)

## Version
### Beta 4 Revision 4

## Changelog
### Additions<br>
-[ClearPos](https://epsirho.github.io/UIKit/#/ClearPos)<br>
-[Clipboard](https://epsirho.github.io/UIKit/#/Clipboard)<br>
-[Font Handling](https://epsirho.github.io/UIKit/#/Font)<br>
-[Mouse Handling](https://epsirho.github.io/UIKit/#/Mouse)<br>
-[Refresh](https://epsirho.github.io/UIKit/#/refresh)<br>
-[Window Handling](https://epsirho.github.io/UIKit/#/Window)<br>
### Changes<br>
-Syntax fixed to be consistant camelCase<br>
-list made a seprate command from upcomming editList command<br>
-mouseChoiceMenu Clicking and highlighting extended<br>
-color command now has overloaded syntax ( `UI::color(int x, int y);` and `UI::color(COORD pos);` )<br>
### Fixes<br>
-mouseChoiceMenu breaking text input<br>
-GetConsoleCursorPosition Not Working<br>
-MouseChoiceMenu bugged when changing Y from 0
-Default Console Color not working
-Menu titles being larger than choices causes clipping issues
-Color not working after syntax change
