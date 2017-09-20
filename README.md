# image-processing-computer-vision-toolbox

First open the Problem-1.cpp file and change the location "/home/pranay/opencv/detect/oscarSelfie.jpg" in double quotes to the location of file oscarSelfie.jpg in your system.

Similarly change the location "/home/pranay/opencv/jellyfish.jpg" of file jellyfish.jpg in Problem-2.cpp file to the location in which the jellyfish.jpg  file is saved in your system.
---------------------------------------------------------------------------------------

Now in order to compile the file Problem-1.cpp write the command in terminal( I am using Ubuntu 14.04 OS)

 g++ -ggdb `pkg-config --cflags opencv` -o `basename Problem-1.cpp .cpp` Problem-1.cpp `pkg-config --libs opencv`

After compiling the file write the command in terminal to run it.

./Problem-1

--------------------------------------------------------------------------------------

Now in order to compile the file Problem-2.cpp write the command in terminal( I am using Ubuntu 14.04 OS)

 g++ -ggdb `pkg-config --cflags opencv` -o `basename Problem-2.cpp .cpp` Problem-2.cpp `pkg-config --libs opencv`

After compiling the file write the command in terminal to run it.

./Problem-2
--------------------------------------------------------------------------------------
