/*
 * Copyright (c) 2026, Voctl
 * SPDX-License-Identifier: BSD-2-Clause
 */

// i will try to write a REPL for sym here

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

#define MAX_INPUT 1024

void takeInput(char *input) {
    printf("\nλ> ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        printf("\nexiting :3\n");
        exit(0);
    }
    input[strcspn(input, "\n")] = 0;
}


int main(void) {
  char input[MAX_INPUT];
  printf("\n\n\n");
  printf("Welcome to sym programming language REPL\nA lightweight language for symbolic and numerical mathematics\n");
  printf("Copyright (c) 2026, Voctl\n");
  printf("SPDX-License-Identifier: BSD-2-Clause");
  while (1){
    takeInput(input);
    if (strlen(input) == 0) continue;
    if (strcmp(input, "denis") == 0) {
      printf("Holy Divine Intellect\n");
    }
  }
  return 0;
}
