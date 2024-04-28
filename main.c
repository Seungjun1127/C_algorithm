#include <stdio.h>
#include "eval.h"

int main() {
    printf("%d", eval_tree(" (1 + 2) * 3"));
    return 0;
}