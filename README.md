# Termial GL

Terminal GL is a graphics library for drawing 16 color graphics in the terminal using text.

## The Goal
The goal of termianl gl to to create an open source graphics library that makes it easy to develop software that can run in the terminal or in text-based graphics mods seamlessly accross all platforms.

### List of Goals for this project
- Good debugging
- Good consistant IO
- Image/Text graphics loading
- Canvas manipulation
- Bleeding edge performance
- Good support for ssh
- Good support for all hardware with text-mode/terminal
- Run Doom on it

## How do I use?
To get started, you need to clone the repo into your project:
```sh
git clone https://github.com/KBOX1234/terminal_gl.git
```
After that, you can include the terminal_gl.h into your project.
You will also have to include a backend into your project.

### Here is an example project
```c
#include <stdio.h>
#include <stdlib.h>
#include "terminal_gl.h"
#include "impl/backend_linux.c"

int main(){
    init_window("test program");
    int xi = 2;
    int yi = 2;
    while(1){
        fill_screen(' ', 0);
        draw_char('&', 1, 1, 0x05);
        draw_text("hello world", 20, 20, 0x05);
        draw_rectangle('#', xi, yi, 6, 6, 0x75);
        draw_line('%', 1, 3, 10, 30, 0x10);
        update();
    }
    return 0;
}
```
This example shows some basic functionality of the library.

You can find a more in-depth tutorial here: [docs/first_project.md](docs/first_project.md)

### Dependancies
This library has no dependacies so building is quite simple.
That said, make sure that your compile can find platform specific libraries that are needed (such as windows.h).
If you want to use image loading, then you will need stb_image.h and add the compiler flag -lm

### Building example
```sh
gcc example.c -o example -Ipath/to/terminal_gl
```
## Backends
Terminal GL uses backends to interface with the OS as apposed to hard codding support in.
This allows for terminal gl to be easily ported to other platforms.
### Creating backends
If your platform does not have a backend, it is pretty easy to make one.
To start, you must check the file impl/impl.h
It contains defenitions for all the functions that terminal gl needs to run.
once you have written the functions, you can now include the backend in you project like this:
```c
#include "terminal_gl.h"
#include "impl/your_backend.c"

int main(){
    return 0;
}
```
## Community
Check out Terminal GL's discord server [here](https://discord.gg/UkDNFYFatQ)

## Libraries that work with TGL
- [Tgl ui](https://github.com/KBOX1234/tgl_gui) easy gui/debbuging library for tgl.
