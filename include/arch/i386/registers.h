#ifndef registers_h
#define registers_h

typedef struct {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int num, err_code;;
    unsigned int eip, cs, eflags, useresp, ss;
} registers_t;

#endif
