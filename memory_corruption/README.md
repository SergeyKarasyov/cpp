# Memory layout
* https://manybutfinite.com/post/anatomy-of-a-program-in-memory/
* Sample linux memory layout
    * text segment (read only, executable instructions, string literals)
    * data segment (initialized static variables)
    * bss segment (uninitialized variables)
    * heap (dynamic allocation), on pop platforms grows towards higher addr.
    * memory mapping segment (dynamic libs, mappings)
    * stack (local variables and function parameters, program stack)
    
* sample code
```
const char* hello_string = "hello"; //data and text
int nums[] = {1, 2};//data
char g_buf[1024];// bss
int main()
{
    char l_buf[1024]; //stack
    char* h_buf = malloc(1024); //heap
    return 0;
}
```
# Memory corruption
* option -Wunitialized prevents unitialized memory from being used (https://gcc.gnu.org/wiki/Better_Uninitialized_Warnings)
* out-of-bounds memory corruption errors fall in two categories:
      * object-based, i.e. when a pointer is used to access target memory;
      * pointer-based, i.e. when the target address is out-of-bounds.
* tools
      * valgrind memcheck
      * kmemcheck uses shadow memory to monitor allocated memory, supports only heap
      * MemorySanitizer is a detector of unitialized read. Consists of compiler and run-time lib. If an error occurs -> prints error message. 
      * AddressSanitizer check for usage of freed or out-of-bounds memory  
      * DieHard, DieHarder allow for avoiding memory reuse by use of special allocators
      * DangNull uses pointer nullification to eliminate pointer dangling.
      * FreeSentry  doesn't change ptr repr., 
      
# Classification of memory corruptions
* buffer overflow - data can be overwritten, hacker cannot control on destination address, hacker can control input data(size and source address)
* arbitrary write - hacker has full control on destination address and input data(size and source address)
* of-by-one - data can be overwritten(usually limited by one element of array), hacker cannot control on destination address, hacker can control input data(only source address)
### buffer overflows
* on stack: local variables, metadate(framepointer, stackpointer)
* heap: dyn allocated memory
* global memory: global variables and structure

### stack
* LIFO
* suports push/pop
* stack pointer points to the next available memory(push - appends elements, and decrements SP, pop - removes element, increments SP)
* each thread has runtime stack (aka call stack, program stack) - it stores local variables, tracks  call chain of functions. Each function has its own part of whole stack - stack frame, when functions are called stack frames are poped/pushed.

### stack anatomy
Every stack frame has three components:
* PC - program counter , to remember where to continue execution after function returns
* FP - frame pointer to remember the base address of calling function's stack frame
* local variables, to store data controlled by the function
### risk with stack corruption
* stack's local variables
* prev stack's local variables
* frame pointer - FP
* frame counter - FC

### heap
* when malloc()(example) is called  - the top chunk is reserved for it(on most archs it's lowest addresses), when this memory is deallocated system should mark the memory as free -> via metadata. 
* when a block of memory is returned to the user it is preceeded by a header. Header describes(size of the current block, size of the previous block,whether the current block is free, optionally some other flags)
* having control over heap it is not possible to overwrite the return address. But possible to corrupt application specific memory, heap metdata. 

### data segment and bss buffer overflow
* global variables can be in bss or in data section. Bss section contains all global and static variables that are initiliazed with zero or are not initialized. Data section containers all initialized static variables. Data segment doesnot change in runtime. 

### arbitrary write
* ability to write to heap, stack, bss, data

### Off-by-one 
* reason may be: termination element is not taken into consideration, array index missunderstood, nconfusin between size of array and the index of last element 
* c-style strings, strcpy() copies null terminator, strlen() doesn't include that
 
 ### Secure coding standards
 * MISRA C
 * CERT C
 * ISO/IEC TS 17691
