## File Editing <!-- {docsify-ignore} -->
#### Info
> Allows the users to edit a text file with a vim-like workspace<br>
> Hit Escape to interact with the top menu
### Syntax
`editFile(std::string filepath);`

* *filepath* - a string with the path a file.

#### Example
```C++
UI::editFile("\\Resources\\Movielist.txt");
