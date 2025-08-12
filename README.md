# heap-memory-allocator

Just a myself-writen test memory allocator for education purpose.

Status: 90% completed. Main logic is done (malloc, realloc, free, memset).

Plans:

1. ~~Malloc/realloc realization;~~
2. ~~Memory cleaner (free func);~~
3. ~~Separate memory allocation logic from main file;~~
4. ~~Add header block for meta-info;~~
5. ~~Fix malloc Segmentaion fault after else condition;~~
6. ~~Memset realization;~~  
7.   Memory defragmentation realization;
8.   ...


Command line and command processing. Architect of data receive mechanism based on NVIC (Nested Vectored Interrupt Controller), means that RXData func calls command handler by '\n' symbol.

Status: in work. Main logic of receive command validation and command processing is done. Must be completed main commands logic.

1. ~~Receive/Transmit symbols logic;~~
2. ~~Receive command validation;~~
3. ~~Commands handler;~~
4.   Commands processing;
5. ~~Separate logic and make encapsulation;~~
6.   Rewrite RXData func architect;
7.   ...