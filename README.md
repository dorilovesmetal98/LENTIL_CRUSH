# Build on Linux

`make -f Makefile_Linux`  

or  

`gcc -O2 -pedantic -Wall -Wextra -Iheader src/text_manipulation.c src/start_screen.c src/playground.c src/pixel_art.c src/main.c src/IO.c src/game_control.c src/field_fill.c src/animation.c src/check_logic.c -o build/lentil_crush`

# Build on Windows

`nmake /F Makefile_Windows`

or  

`cl -Iheader src/text_manipulation.c src/start_screen.c src/playground.c src/pixel_art.c src/main.c src/IO.c src/game_control.c src/field_fill.c src/animation.c src/check_logic.c /link /out:build/Lentil_Crush.exe`