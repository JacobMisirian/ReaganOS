#ifndef idtRegister_h
#define idtRegister_h

typedef struct {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int num, err_code;;
    unsigned int eip, cs, eflags, useresp, ss;
} idtRegister_t;

#endif
