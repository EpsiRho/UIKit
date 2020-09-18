## Clipboard Handling <!-- {docsify-ignore} -->

## Copy text from the clipboard
#### Info
> Returns a string of text from the clipboard if there is any
#### Syntax
`std::string copyFromClipboard();`

#### Example
```C++
std::string str_input = UI::copyFromClipboard();
```

## Copy text to the clipboard
#### Info
> Puts of string into the clipboard
#### Syntax
`void copyToClipboard(std::string str);`
* *str* - the text to be sent to the clipboard

#### Example
```C++
UI::copyToClipboard("www.website.com");
```