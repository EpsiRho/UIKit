## Login Menu <!-- {docsify-ignore} -->
#### Info
> Displays a menu with multiple input locations<br>
> Returns a vector of strings in the order they were input
> Choices MUST be terminated with NULL
### Syntax
`pathMenu(COORD pos, const char* choice, NULL);`

* *pos* - a COORD with the x and y position for the window to be placed
* *choice* - Takes as many strings as inputed and uses them as the prompts for each sub menu
* *NULL* - Tells the command to stop looking for string arguments

#### Example
```C++
std::vector<std::string> usr_rtrn = UI::pathMenu(pos, "FTP Login", "Host", "Username", "Password", NULL);
connect(usr_return[0], usr_return[1], usr_return[2]);
```

#### Output
```
FTP Login
▌Host:
▌Username:
▌Password:

```
