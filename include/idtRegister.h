#ifndef idtRegister_h
#define idtRegister_h

typedef struct {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;;
    unsigned int eip, cs, eflags, useresp, ss;
} idtRegister_t;

unsigned char * exceptionMessages [] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Reserved",
    "Reserved"
};

#endif
