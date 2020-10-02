## Beta 4 Release
### Additions<br>
- [ClearPos](https://epsirho.github.io/UIKit/#/ClearPos)<br>
- [Clipboard](https://epsirho.github.io/UIKit/#/Clipboard)<br>
- [Font Handling](https://epsirho.github.io/UIKit/#/Font)<br>
- [Mouse Handling](https://epsirho.github.io/UIKit/#/Mouse)<br>
- [Refresh](https://epsirho.github.io/UIKit/#/refresh)<br>
- [Window Handling](https://epsirho.github.io/UIKit/#/Window)<br>
### Changes<br>
- Syntax fixed to be consistant camelCase<br>
- list made a seprate command from upcomming editList command<br>
- mouseChoiceMenu Clicking and highlighting extended<br>
- color command now has overloaded syntax ( `UI::color(int x, int y);` and `UI::color(COORD pos);` )<br>
### Fixes<br>
- mouseChoiceMenu breaking text input<br>
- GetConsoleCursorPosition Not Working<br>
- MouseChoiceMenu bugged when changing Y from 0<br>
- Default Console Color not working<br>
- Menu titles being larger than choices causes clipping issues<br>
- Color not working after syntax change<br>

## Plans for Beta 5 Release<br>
- Functions with Args overload with vectors.<br>
- Demo Application Complete<br>
- Editable List<br>
- Screenshot<br>
- Multiple Progres Bars<br>
- loginMenu<br>

## Beta 5 Revision 1<br>
### Fixes<br>
- Fixed Text Menu<br>
- Fixed broken input after mouse input disable<br>
- Switched from std::cout to fwrite(through TextMenu, pathMenu and below needs to be finished)<br>

## Beta 5 Revision 2<br>
### Removed<br>
- pathMenu has been removed. Will be replaced by loginMenu Function in Revision 3.<br>
### Docs<br>
- ProgressBar docs now have info on set_status_text<br>
### Demo<br>
- Demo now shows set_status_text example<br>
- pathMenu Choice replaced with loginMenu, Does not currently function<br>
### Improvements<br>
- all std::cout removed and switched to fwrite<br>