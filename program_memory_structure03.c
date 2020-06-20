int global_variable;	/* Uninitialized global_variable stored in bss section */

void main(void){
	static int i;		/* Uninitialized static int stored in bss section */
	while(1);
}
