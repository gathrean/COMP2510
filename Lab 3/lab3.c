#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int x;
    int y;
    struct Node *next;
};

void drawShape (struct Node* n, FILE *fop, int x_min, int x_max, int y_min, int y_max) {
    for (int j = y_max; j >= y_min; j--) {
        for (int i = x_min; i <= x_max; i++) {
            struct Node *curr = n;
            while (curr != NULL) {
                if (curr->y == j && curr->x == i) {
                    fprintf(fop, "*");
                    break;
                }
                curr = curr->next;
            }
            if (curr == NULL) {
                fprintf(fop, " ");
            }
        }
        fprintf(fop, "\n");
    }
}

int main(int argc, char *argv[]) {

    struct Node* head;
    struct Node* tail;
    struct Node* temp;

    FILE *fip, *fop;
    int node_num = 0;
    int xp = 0, yp = 0, x_max = 0, y_max = 0, x_min = INT_MAX, y_min = INT_MAX;
    // INT_MAX from limits library.

    int x, y, xOut, yOut;

    fip = fopen(argv[1], "r");
    fop = fopen(argv[2], "w");

    head = NULL;
    tail = NULL;
    temp = NULL;

    while(fscanf(fip, "%d,%d", &x, &y) == 2) {
        if (head == NULL) {
            xp = x;
            yp = y;
            head = (struct Node*) malloc(sizeof(struct Node));
            head->x = xp;
            head->y = yp;
            tail = head;
        } else {
            while (xp != x || yp != y) {
                if (xp < x) {
                    xp++;
                }
                if (xp > x) {
                    xp--;
                }
                if (yp < y) {
                    yp++;
                }
                if (yp > y) {
                    yp--;
                }
                temp = (struct Node*) malloc(sizeof(struct Node));
                temp->x = xp;
                temp->y = yp;
                temp->next = NULL;
                tail->next = temp;
                tail = temp;
                node_num++;
            }
            xp = x;
            yp = y;

            if (xp > x_max) {
                x_max = xp;
            }
            if (yp > y_max) {
                y_max = yp;
            }
            if (xp < x_min) {
                x_min = xp;
            }
            if (yp < y_min) {
                y_min = yp;
            }
        }
    }

    drawShape(head, fop, x_min, x_max, y_min, y_max);

    fclose(fip);

    free(head);
    free(temp);

    return 0;
}

