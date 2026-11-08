/*
 * Copyright (c) 2026, Voctl
 * SPDX-License-Identifier: BSD-2-Clause
 */

// i will try to make a REPL for sym here


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT 1024

void takeInput(char *input) {
    printf("\n$ ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        printf("\nexiting :3\n");
        exit(0);
    }
    input[strcspn(input, "\n")] = 0;
}


int main(void) {
  char input[MAX_INPUT];

  while (1){
    takeInput(input);
    if (strlen(input) == 0) continue;
  }
  return 0;
}
