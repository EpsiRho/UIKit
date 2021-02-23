# Window Handling <!-- {docsify-ignore} -->

## Fullscreen
> You can enable and disable the fullscreen mode with:<br>
> `enableFullscreen();` and `disableFullscreen();`

## Scrollbar
> You can show and hide the scrollbar with:<br>
> `showScrollbar();` and `hideScrollbar();`

## Adjusting the window Height
#### Info
> setWindowSize can change the size of the window.<br>
> **This is depended on the current font size**
#### Syntax 
`setWindowSize(int Width, int Height);`

* *Width* - An integer value representing the desiered width
* *Height* - An integer value representing the desiered height

## Getting the current window size
#### Info
> Returns a COORD with the x being the width and the y being the height<br>
#### Syntax
`getWindowSize();`

