# Your first project
Hello, this tutorial talks about creating a small project start to finish.

## Chapters
- Setup
- Code (where the fun begins)
- Building


## Setup
- Clone project
- Download dependancies

### Cloning the project
Now, you will want to clone the library into your project root folder.
Here is how you do that:
```sh
git clone https://github.com/KBOX1234/terminal_gl.git 
```

### Download dependancies
Next you will need to download stb_image.h, however, if you don't enable IMG_LOADING in your project, you will not need to do this.
Download [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) from github and past it in your project root folder.

## Code (where the fun begins)
Now for the fun stuff.
Now you are going to want to create a file called "main.c" in your project root.
Open the folder with your code editor of choise and begin writing in main.c. 
```c
#include <stdio.h>
#include <stdlib.h>
#include "terminal_gl.h"
#include "impl/backend_linux.c"
int main(){
    //init terminal GL
    init_window("my first tgl project");
    //main game loop
    while(1){
        //clears the screen black
        fill_screen(' ', 0);
        //draws text at x = 20 and y = 20 with vga color code 0x05
        draw_text("hello world", 20, 20, 0x05);
        update();
    }
    return 0;
}
```
**NOTE!** For windows users, replace:
```c
#include "impl/backend_linux.c"
```
with:
```c
#include "impl/backend_windows.c"
```
Ok, so what are we seeing here?
The first line we care about is this:
```c
init_window("my first tgl project");
```
This line sets up terminal gl. 
Its main job is to set the pid name and the window name to the argument passed.
It also will run any platform specific code needed to run on start (for example linux needs to allocate a 3rd buffer becaus of how it can only reliably handle colors as ansi codes).
Moving on to the while loop, inside we first come accross this command:
```c
fill_screen(' ', 0);
```
Just in case it is not obvius, fill_screen() fills the screen.
The first argument accepts a char value that represents a charectur to fill the screen with.
The second argument accepts a VGA/DOS style color code. The color is 4 bits but accepts a whoal 8 bit char.
This is so that you can pass the forground color on the first 4 bits and the background color on the last 4 bits.
Here is a good resource for understanding VGA color codes: [www.fountainware.com](https://www.fountainware.com/EXPL/vga_color_palettes.htm)

On the next line we have this:
```c
draw_text("hello world", 20, 20, 0x05);
```
This line draws text to the screen.
The first argument accepts a C style string and the next 2 values accepts the x and y of where the string will begin drawing.
The last argument is the color of the text using a VGA style color code like the one used in the previous command.

Last but not least, we have this line:
```c
update();
```
It is important to remember this command becaus without it, your program will not show anything.
The update command is task with drawing all the buffer and color data to the screen using low level commands to run as fast as possible.

## Building
Now it is time to see the fruits of our labor and see what this code does.
### What your project should look like
To avoid any frustraion amoungst newer programmers, I will show you what your project structure should look like:
- Project root
- - main.c
- - terminal_gl
- - stb_image.h
-
If thats what your project looks like, then you should be all set to compile it.
### Compiling with gcc
Now its time to compile our program.
To compile, open up a terminal and CD into the project root directory.
Once you have done that, run this command to compile it:
```sh
gcc main.c -o program -I./terminal_gl -lm
```

If your program compiled succsefully, then you should have an excutable called program (program.exe on windows).

# Congrats
You have compleated the tutorial level :))
