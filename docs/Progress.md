# Progress Bars <!-- {docsify-ignore} -->
## Single Progress Bar Class
#### Info
> Displays a Progress bar with the characters of your choice<br>
> Only one can run at a time
#### Usage
* Define the Progressbar:<br>
`ProgressBar varName;`
* Set the Width(number of characters) it will take up:<br>
`varName.set_bar_width(size_t width);`
* Set the character that the bar will be filled with:<br>
`varName.fill_bar_progress_with(const char& ch);`
* Set the character that the bar starts with:<br>
`varName.fill_bar_remainder_with(const char& ch);`
* Update the Progress Bar:<br>
`varName.update(COORD pos, float value);`
* Set the Status Text displayed at the end of the bar:<br>
`varName.set_satus_text(std::string);`

#### Example
```C++
UI::ProgressBar bar;
bar.set_bar_width(100);
bar.fill_bar_progress_with((char)219);
bar.fill_bar_remainder_with((char)176);

UI::ClearScreen();

do {
	char buffer[10245];
	if (size > 10240) {
		file.read(buffer, 10240);
		send(ftp.data, buffer, 10240, 0);
	}
	else {
		file.read(buffer, size);
		send(ftp.data, buffer, size, 0);
	}
	size -= 10240;
	bar.update(pos,((oSize - size) * 100) / oSize); // Update Progress Bar
} while (size > 0);
```

#### Output
```
[████████████████████████████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░] 39%
```

## Multiple Progress Bars Class
**UNIMPLEMENTED**