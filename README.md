-- Under construction --

gclip
=====

Gclip is a simple stack-based clipboard utility for the command line. 
It is interfaces through a char device file (/dev/gclip). Clippings
are written to this file and added to a stack. Reading from the file
yields (and removes) the top clipping in the stack.

Usage
=====
To install gclip: <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;tar -xvf gclip.tar.gz <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cd gclip <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;make <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sudo make install <br />
  <br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Note: If you wish to create the device file yourself, skip the install step

To use: <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;echo "Hello" > /dev/gclip <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;echo "World" > /dev/gclip <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cat /dev/gclip <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$ World <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;cat /dev/gclip <br />
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$ Hello <br />

Details
=======

Gclip is a kernel module that is interfaced through a char device file.
Characters are read in until an EOF is indicated, at which point stack
memory is allocated and the clipping is placed on the stack. Reading 
from /dev/gclip will yield characters until the end of thc clipping is
reached, at which point gclip will fail to return further data until 
another write request is made. 
