#include <stdio.h>

static char only_in_file_str[] = "Accessible only in file";
float test_extern_float = 1.11111f;

extern int global_counter;
void display();

static void local_func() {
    printf("This is only accessble within test_variables.c!\n");
}

void test_variables(float increment) {
   static float local_persistent = 2.2222f;
   register int reg_var = 9999;
   int block_scoped = 10;
    
  
  printf("Block scoped variable: %d\n", block_scoped);
  printf("Variable accessible only in file: \"%s\"\n", only_in_file_str);

  local_persistent += increment;

  printf("Local persistent variable: %.2f\n", local_persistent);
  printf("Register variable: %d\n", reg_var);
  printf("Calling local only func...\n");
  local_func();
}

void display() {
    global_counter++;
    printf("Global counter is %d\n", global_counter);
}
