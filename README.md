# Game Loop, Input, Frames

## Setup
- You can change the controls by typing the input source and a number corresponding to a button.
- Refer to [raylib.h](https://github.com/raysan5/raylib/blob/master/src/raylib.h) for the input enums
- Examples
- - `keyboard 53` means the keyboard key corresponding to 53 (the "5" key)
- - `mouse 2` means the mouse button corresponding to 2 (the middle mouse button)

## Default Controls
- Pressing spacebar emits particles from the bottom center of the window.
- Left-clicking and dragging with the mouse emits particles from the cursor position.
- The left and right arrow keys decrease and increase the emission rate of the particles emitted from the bottom center of the window.
- The down and up arrow keys decrease and increase the emission rate of the particles emitted from the cursor position.
