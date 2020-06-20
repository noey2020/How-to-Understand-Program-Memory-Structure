int global_variable;	/* Uninitialized global_variable stored in bss section */

void main(void){
	static int i = 1;	/* Initialized static int stored in data section */
	while(1);
}
