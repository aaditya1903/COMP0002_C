#include <stdio.h>
#include <stdlib.h>

int countCharacter(const char* str, char ch) {
    int count = 0;
    
    while (*str != '\0') {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    
    return count;
}

int* countVowels(const char* str) {
    int* vowelCounts = (int*)malloc(5 * sizeof(int));
    if (vowelCounts == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    for (int i = 0; i < 5; i++) {
        vowelCounts[i] = countCharacter(str, "aeiou"[i]);
    }
    
    return vowelCounts;
}

void printVowelCounts(const int* vowelCounts) {
    if (vowelCounts == NULL) {
        return;
    }
    
    printf("Vowel Counts: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", vowelCounts[i]);
    }
    printf("\n");
}

int main() {
    const char* str = "This is some text";
    
    int* vowelCounts = countVowels(str);
    printVowelCounts(vowelCounts);
    
    free(vowelCounts);
    
    return 0;
}