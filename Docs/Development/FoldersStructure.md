<!--
* ++
*
* Copyright (c) 2023 JulesIMF, MIPT
*
* Module Name:
*
*     FoldersStructure.md
*
* Abstract:
*
*     Description of project structure.
*
* Author / Creation date:
*
*     JulesIMF / 17.03.23
*
* Revision History:
* 
* --
*
-->

# Structure of folders

Viper is being written in C++ using Clang compiler & tools along with CMake.

Main code lies in Source folder.

## Docs
All language documentation is kept here. Look at [[Docs/Main]].md to navigate through the documentation.

### Docs/Development
Everything related to Viper development, including this document.

### Docs/Examples
Viper demo programms & code.

### Docs/Grammar
Everything related to Viper grammar structure.

## Includes
All header files lie here. Some Its structure mirrors Source folder structure.

## Source
All main C++ code lies here along with Includes folder. Code from this folder is exported to libviperlang.

### Common
Some common utility functions and structures, that cannot be classified as parts of more serious subsystems, are implemented here.

### Lex
Lexicographical analyzer (tokenizer) implementation.

### Misc
Miscancellous things, mostly scripts.

## Tests
Some tests. Subfolders mirror source and tree structure.