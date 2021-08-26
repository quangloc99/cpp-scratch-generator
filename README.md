# CppScratchGenerator

Do you like [Scratch](https://scratch.mit.edu/)? Well for me, not really. The
coding part became surprisingly lengthy.  So here I made a ~simple~ library to
overcome that part.

This library is still need more work, and I made this more or less like a toy
project. It got potential to actually support all of the blocks, but for now
this library is like a proof of concept.


## Compatibility
Currently this library only support generating blocks with the following 
constraints:
- Variables and lists are only be declared in the global scope (that is, they
are associated with the `Stage`).
- All of the program's blocks are currently associated with the sprite `Sprite1`
(or the default sprite).
- The current interaction with the program is via the blocks `ask and wait`
block in the sensing section for `input` and `think/say` for the output.

If you noticed, these are the very basic things supported by
[Scrape](https://github.com/scraterpreter/scrape), a Scratch interpreter.
The current state of this library support _almost_ everything that scrape does,
with 1 exception - this library also got procedure!

## Installation
To use the library, you only need 3 file in this project:
- `cpp-scratch-generator.hpp` - contains all of the logic.
- `def-macro.inc` - contains all of the macro that made writing code more trivial.
- `undef-macro.inc` - cleans up all of the macro inside `def-macro.inc`.

## Usage
All of your program logic for Scratch should be defined in 1 function that
accepts no argument and returns `void`. You can write _almost_ C++ code with
a few small exception that will be mentions in the Doc. 

The goal of this library is to generate the `project.json` file, and that
file is the core of the `*.sb3` file. To generate `project.json` file,
use the function
`CppScratchGenerator::generate_project_json(ostream&, <you function here>);`.

Typically you should use the template below (which is also the file
`./boilerplate.cpp`.


```c++
#include <iostream>
#include <fstream>
#include "cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "def-macro.inc"
    // your code here
#include "undef-macro.inc"
}

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
```

## Docs
> TODO


