Virus Infection and Mutation Project

Project Overview:
This project implements a simulated virus that infects other binary files. The virus uses a prepend technique, attaching itself to the beginning of a target file, while the original content of the file is preserved for execution. Each infection involves a unique mutation of the virus code, altering the hash of each infected file to evade hash-based detection mechanisms.

Proj2
├── Source
│   ├── virus.cpp        # Source code for the virus
│   ├── host.cpp         # Host binary source code to be infected
│   └── makefile         # Build file for compiling the virus and host
├── authors.txt		 # Identification of authors
├── README.txt           # Project documentation (this file)

Prerequisites:
C++ Compiler: The project requires a C++ 14 compatible compiler
Linux Environment: This implementation is tested in a Linux environment
Standard Libraries: iostream, fstream, cstdlib, ctime, cstring, unistd.h

Setup Instructions:
1) Clone the repository
git clone https://github.com/TylerLynch1/basic-virus.git

2) Compile the Virus and Host Binaries
make

* Note * The make command will produce six binaries:
host
virus
seed
victim1
victim2
victim3

* Note *  The seed binary is composed of the host binary being concatenated to the seed

Usage:
1) Run the seed on a victim file to infect it
./seed ./victim1

2) Run the infected victim file on another victim binary
./victim1 ./victim2

3) Repeat

Mutation Strategy:
The mutation strategy introduces a unique, random sequence of bytes to the virus code upon each infection, altering the virus binary slightly while preserving its functionality. This approach leverages a random number generator to insert variable data at predefined points within the virus, effectively changing its hash value with each infection and evading hash-based detection.
