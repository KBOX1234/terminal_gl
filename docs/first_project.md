# Your first project
Hello, this tutorial talks about creating a small project start to finish.

## Chapters
- Setup
- Code (where the fun begins)
- Build 


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
```
