#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

void insert(struct node **root, int data) {
    if (*root == NULL) {
        *root = (struct node*)malloc(sizeof(struct node));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else if (data < (*root)->data) {
        insert(&(*root)->left, data);
    } else {
        insert(&(*root)->right, data);
    }
}

void print_inorder(struct node *root, FILE *output) {
    static int prev_data = -1; // initialize to an impossible value
    if (root != NULL) {
        print_inorder(root->left, output);
        if (root->data != prev_data) {
            fprintf(output, "%d\n", root->data);
            prev_data = root->data;
        }
        print_inorder(root->right, output);
    }
}

int main(int argc, char *argv[]) {

    // Check for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Could not open input file\n");
        return 1;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Could not open output file\n");
        return 1;
    }

    struct node *root = NULL;
    int data;
    while (fscanf(input, "%d", &data) == 1) {
        insert(&root, data);
    }
    print_inorder(root, output);
    fclose(input);
    fclose(output);
    return 0;
}