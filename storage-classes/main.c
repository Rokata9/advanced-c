#include <stdio.h>
#include "test_variables.h"

extern float test_extern_float;
extern void display();

int persistent_sum(int num);
void global_in_loop();

int global_counter = 0;

int main() {
    /* printf("*********** First call of test variables: \n"); */
    /* test_variables(0.5f); */

    /* printf("*********** Second call of test variables: \n"); */
    /* test_variables(0.5f); */

    /* printf("External float is %.2f\n", test_extern_float); */

    /* printf("Persistent sum test:\n"); */
    /* printf("%d ", persistent_sum(25)); */
    /* printf("%d ", persistent_sum(15)); */
    /* printf("%d ", persistent_sum(30)); */
    /* printf("\n"); */

    global_in_loop();
}

int persistent_sum(int num) {
    static int acc = 0;
    acc += num;
    return acc;
}

void global_in_loop() {
  for (int i = 0; i < 5; i++) {
      display();
  }
}
