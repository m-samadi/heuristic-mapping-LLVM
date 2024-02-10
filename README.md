# Implementation of heuristic task-to-thread mapping in LLVM
This repository contains the implementation sources of four heuristics used in a heuristic task-to-thread mapping for OpenMP. The code also includes a feature to record the mapping of tasks by threads.
<br/>
<br/>

## LLVM version
The implementation is carried out based on the BSC LLVM available at https://gitlab.bsc.es/ampere-sw/wp2/llvm/. The instructions to install it are available at https://gitlab.bsc.es/ampere-sw/wp2/general-information/. Note that the sources are compiled with the latest version 17.0.0.
<br/>
<br/>

## Heuristic algorithms
The heuristic task-to-thread mapping is a scheduler for the OpenMP framework, which consists of two phases: allocation and dispatching. Tasks are allocated to the allocation queues of threads in the former phase, while they are deallocated from the queues and then dispatched to the processor cores in the latter phase. Accordingly, four heuristic algorithms are presented for this mapping, where two of them (i.e., MNTP and MTET) are provided for the allocation phase and the others (i.e., MET and HET) are provided for the dispatching phase.
<br/>
<br/>

MNTP selects the allocation queue with the minimum number of task parts, MTET selects the queue with the minimum total execution time, MET selects the task with the minimum execution time from the allocation queue, and HET selects the task with the highest execution time from the queue.
<br/>
<br/>

## Update the LLVM
After installing LLVM on the system, the *kmp.h* and *kmp_tasking.cpp* files located in the path "/openmp/runtime/src" in the source directory of LLVM should be replaced with those provided in the root of the repository. Note that two variables (including ALLOC_TYPE and DSPCH_TYPE) are provided in *kmp_tasking.cpp* to switch between the basic LLVM scheduler and the heuristic mapping. Then, LLVM should be rebuilt using the following command to make the changes:
```C
sudo ninja install
```
<br/>

## Run the program
To run an OpenMP-based program (e.g., the *heat* application is provided in the repository) based on the heuristic mapping, the program (located in the path "/heat/source" of the repository) should be first compiled and built as below:
```C
make
```
Then, the *heat_tdg.cpp* and *tdg.hpp* files (which are created with LLVM by default) should be replaced with the sources located in the path "/heat/update" of the repository. The new sources include the *exe_time* attribute (i.e., task execution time) that is used with the heuristic algorithms. The program should be rebuilt using the following command to make the changes:
```C
clang -fopenmp heat.o heat_tdg.cpp misc.c -L${LLVM_PATH}/llvm/lib -O2 -o heat -lm
```
Note that *LLVM_PATH* is the installed path of LLVM. Finally, the program can be executed using the following command:
```C
./heat test.dat
```
