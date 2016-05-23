# Inexor Tree API Gluecode Generator

This is a prototypical gluecode generator for the [ Inexor Tree API ]( https://github.com/inexor-game/code/wiki/Inexor-Tree-API ).

At the moment it can list all the SharedVars and their underlying storage types in their canonical forms.
The output should be `(TYPE) VAR_NAME_WITH_NAMESPACe`.

In the future it should be expanded to use this information
to generate protobuf files mirroring that information and to
use those for applying and generating differential state
updates.

Beyond that support for Data Structures needs to be added.

The gluecode generator uses libclang with clang's libtooling to generate a standalone analyzer.
In the future it should be possible to run this as a clang
plugin in order to avoid the additional compilation step.

## Running

You need clang installed and the usual UNIX C programming
tools (e.g. make). And the libraries also used for building
inexor.

Then just invoke:

`make run`


## Building the reflection lib (the gluegenerator)

Firstly you need to install the dev files of llvm and clang.  
To do this on Linux, probably the according -dev packages are enough,
for Windows you need to compile llvm (+ clang) yourself.
Follow this tutorial: http://clang.llvm.org/get_started.html since thats what we use as directory structure
for our build tool.  

For windows you **must** set the in the cmake-gui to MTd for and MT for the other ..
To minimize the build times you can additionally disable a lot of build targets for clang/llvm:


CLANG_BUILD_EXAMPLES [DISABLE]  
CLANG_INCLUDE_DOCS   [DISABLE]  
CLANG_INCLUDE_TESTS  [DISABLE]  
CLANG_INSTALL_SCANBUILD [DISABLE]  
CLANG_INSTALL_SCANVIEW  [DISABLE]  

LLVM_BUILD_TOOLS      [DISABLE]  
LLVM_INCLUDE_DOCS     [DISABLE]  
LLVM_INCLUDE_EXAMPLES [DISABLE]  
LLVM_INCLUDE_GO_TESTS [DISABLE]  
LLVM_INCLUDE_TESTS    [DISABLE]  
LLVM_INCLUDE_TOOLS    [DISABLE]  
LLVM_INCLUDE_UTILS    [DISABLE]  

Edit:
**CMAKE_INSTALL_PREFIX to the folder you want to install your libs into**, to have them all together later.
**For Windows when building with VS** you need to set:

LLVM_USE_CRT_DEBUG          [MTd]  
LLVM_USE_CRT_MINSIZEREL     [MT]  
LLVM_USE_CRT_RELEASE        [MT]  
LLVM_USE_CRT_RELWITHDEBINFO [MT]  

Enable:
LIBCLANG_BUILD_STATIC [ENABLE]  
LINK_POLLY_INTO_TOOLS [ENABLE]  


However for windows you

Then build the 'INSTALL' target, to get all libs in one place.

Therefore you may just 


After that, you need to edit the cmake file accordingly

