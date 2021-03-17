To run the code on a Mac through the command line:

1. Download Makefile from this section

2. Put Makefile in same directory as IsingSystem.cpp (! Remove the .txt extension if present !)

3. Relative to MS Visual Studio code, these files include the following changes: IsingSystem.h Window.h MAIN_Source.cpp

change #include <gl/freeglut.h>

to #include <GLUT/glut.h>

4. Open the terminal in the same folder as these files

5. Type "make" to build project

6. Run the program by typing "./run"

7. To edit your files, run gedit, save the code, and recompile with "make -B" before running the program again.



Thanks to Eliot Ayache for figuring this out!



PS For Coursework 2: In addition, there needs to be a change in Line 72 of MAIN_Source.cpp file from "glutLeaveMainLoop();" to "exit(1);"