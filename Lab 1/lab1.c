// Do NOT touch this function signature
void printMultiplicationTable(int n) {

}
#include <stdio.h>
int main(int argc, char **argv){

    int i, j, n;
    printf("Enter number: ");
    scanf("%d", &n);
    printf("\n");

    // Prints the first row that starts with X.
    printf("X\t");
    for (j = 0; j <= n; j++)
        printf("%d\t", j);
    printf("\n");

    // First column
    for (i = 0; i <= n; i++) {
        printf("%d\t", 1 * i);

        // Rows
        for (j = 0; j <= n; j++)
            printf("%d\t", i * j);

        printf("\n");
    }
    return 0;
}