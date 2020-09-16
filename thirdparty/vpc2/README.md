## VPC2

This is an extended version of VPC based on the Source Engine 2017 leak. This code was pulled from the TF2 branch.

## Features

* Support for Visual Studio Code workspaces 
* Support for clangdb compilation databases (compile_commands.json) 
* Support for generating CMake scripts for better integration with IDEs like CLion
* Vastly improved codelite support

## Building


### Linux

Building can be done on Linux by running `make` in the root directory of the repository. 

Running `make install PREFIX=my_prefix` will install `vpc_linux32` to `my_prefix/devtools/bin/vpc_linux32`.

### Windows

Currently not supported, but I'm going to get this going on Mingw eventually.

## Usage

It's largely the same as normal VPC. 

* For the cmake generator pass `/cmake` 
* For the vscode generator pass `/vscode`
* For the codelite generator pass `/codelite`
* For the clangdb generator pass `/clangdb`