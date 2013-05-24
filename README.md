-- Under construction --

gclip
=====

Gclip is a simple stack-based clipboard utility for the command line. 
It is interfaces through a char device file (/dev/gclip). Clippings
are written to this file and added to a stack. Reading from the file
yields (and removes) the top clipping in the stack.

Usage
=====
To install gclip:
  tar -xvf gclip.tar.gz
  cd gclip
  make
  sudo make install

To use:
  echo "Hello" > /dev/gclip
  echo "World" > /dev/gclip
  cat /dev/gclip
    $ World
  cat /dev/gclip
    $ Hello

Details
=======

Gclip is a kernel module that is interfaced through a char device file.
Characters are read in until an EOF is indicated, at which point stack
memory is allocated and the clipping is placed on the stack. Reading 
from /dev/gclip will yield characters until the end of thc clipping is
reached, at which point gclip will fail to return further data until 
another write request is made. 
