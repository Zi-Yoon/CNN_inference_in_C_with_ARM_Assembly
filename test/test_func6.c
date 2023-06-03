#include <stdio.h>

void sendstr(const char* str) {
    printf("%s", str);
}

void printDecimal(int num) {
    printf("%d", num);
}

void output_pixels(unsigned char* after_pooling, unsigned int x, unsigned int y) {
    sendstr("(R : ");
    printDecimal((int)*(after_pooling + 3 * y + x * 3));     // r [x][y]
    sendstr(", G : ");
    printDecimal((int)*(after_pooling + 3 * y + x * 3 + 1)); // g [x][y]
    sendstr(", B : ");
    printDecimal((int)*(after_pooling + 3 * y + x * 3 + 2)); // b [x][y]
    sendstr(")\n");
}

int main() {
    unsigned char after_pooling[] = { 12, 21, 13, 22, 34, 10, 25, 81, 11 };
    unsigned int x = 1;
    unsigned int y = 1;

    output_pixels(after_pooling, x, y);

    return 0;
}
