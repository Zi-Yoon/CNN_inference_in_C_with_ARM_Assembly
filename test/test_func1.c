#include <stdio.h>
#include <stdlib.h>

int convertToFixedPoint(unsigned char value) {
    return (int)((int)value << 16);
}

void printBinary(int value) {
    printf("%08X ", value);
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printBinary(array[i]);
    }
    printf("\n");
}

int main() {
    unsigned char data = 0x42;
    unsigned char first_set[] = { 0x42, 0x82, 0xB0 };
    unsigned char second_set[] = { 0x3C, 0x11, 0x1A };

    int fixedPointData = convertToFixedPoint(data);

    printf("Fixed-point data: ");
    printBinary(fixedPointData);
    printf("\n");

    int* memory = (int*)malloc(6 * sizeof(int));

    for (int i = 0; i < 3; i++) {
        memory[i] = convertToFixedPoint(first_set[i]);
        memory[i + 3] = convertToFixedPoint(second_set[i]);
    }

    printf("Stored data in memory: ");
    printArray(memory, 6);

    unsigned int* ptr = (unsigned int*)malloc(6 * sizeof(unsigned int));
    unsigned int row1[] = { 0x42, 0x82, 0xB0 };
    unsigned int row2[] = { 0x3C, 0x11, 0x1A };
    int rows = 2;
    int cols = 3;

    for (int i = 0; i < cols; i++) {
        ptr[i] = row1[i] << 16;
    }

    for (int i = cols; i < rows * cols; i++) {
        ptr[i] = 0;
    }

    for (int i = 0; i < cols; i++) {
        ptr[cols + i] = row2[i] << 16;
    }

    for (int i = cols; i < rows * cols; i++) {
        ptr[cols + i] = 0;
    }

    printf("Stored data in ptr: \n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printBinary(ptr[i * cols + j]);
        }
        printf("\n");
    }

    free(memory);
    free(ptr);

    return 0;
}
