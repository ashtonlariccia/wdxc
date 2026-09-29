#include <stdlib.h>

int main(int argc, char **argv, char **envp);

_Noreturn void __start_c(long *sp) {
    int argc = (int)sp[0];
    char **argv = (char **)&sp[1];
    char **envp = (char **)&sp[argc + 2];

    exit(main(argc, argv, envp));
}
