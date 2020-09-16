## Text Wrapping <!-- {docsify-ignore} -->
#### Info
> Wraps text with or without a bounding box<br>
#### Syntax
`Wrapper(COORD pos, std::string text, int wrap, int border);`

* *pos* - a COORD with the x and y position for the window to be placed
* *text* - The text to wrap
* *wrap* - The number of character to print on one line before wrapping
* *border* - **Either 0 for no border** or **1 for Border**

#### Example
```C++
UI::Wrapper(pos, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non arcu id ligula ultrices feugiat. Etiam pellentesque magna eu libero elementum auctor. Ut eu eleifend tellus, ornare sodales sapien. Mauris laoreet urna ac rutrum luctus. Suspendisse semper leo lacus, sed accumsan nulla vehicula nec. Nam posuere dui sed pretium convallis. Nulla viverra tellus ac elementum tristique. Mauris sit amet mauris enim.",
50, 1);
```

#### Output
```
┌────────────────────────────────────────────────────┐
│ Lorem ipsum dolor sit amet, consectetur adipiscing │
│  elit. Sed non arcu id ligula ultrices feugiat. Et │
│ iam pellentesque magna eu libero elementum auctor. │
│  Ut eu eleifend tellus, ornare sodales sapien. Mau │
│ ris laoreet urna ac rutrum luctus. Suspendisse sem │
│ per leo lacus, sed accumsan nulla vehicula nec. Na │
│ m posuere dui sed pretium convallis. Nulla viverra │
│  tellus ac elementum tristique. Mauris sit amet ma │
│ uris enim.                                         │
└────────────────────────────────────────────────────┘
```