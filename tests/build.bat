set PATH=%PATH%;c:\\raylib\\w64devkit\\bin
g++ main.c -o UnderGround.exe -lraylib -lopengl32 -lgdi32 -lwinmm -g -limgui -I/lib -I/lib/rlImGui-main/ -I/shared -Ic:/raylib/raylib/src/ -I/lib/stb -Wl,--stack,14194304
UnderGround
