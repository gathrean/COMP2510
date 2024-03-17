#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 20
#define COL 20

typedef struct Point {
  int x, y, vx, vy;
  struct Point *next;
} Point;

void move(FILE *fp, struct Point part[], int sec, int num_part) {
  //move times
  for (int i = 0; i < sec; i++) {
    //velocity check
    for (int j = 0; j < num_part; j++) {
      part[j].x += part[j].vx;
      part[j].y += part[j].vy;
    }
  }
}

void colcheck(struct Point part[], int *part_num) {
  for(int i = 0; i < *part_num; i++) {
    int col = 0;
    for (int j = i + 1; j < *part_num; j++) {
      if(part[i].x == part[j].x && part[i].y == part[j].y) {
        col++;
      }
    }
  }
}

void print(FILE *fp, struct Point part[], int num_part) {
  //top
  for(int i = 0; i < COL + 2; i++) {
    fprintf(fp, "*");
  }
  fprintf(fp, "\n");

  //left border upside down
  for (int j = ROW -1; j >= 0; j--) {
    fprintf(fp, "*");
    
    for (int i = 0; i < COL; i++) {
      int found = 0;
    
      for (int k = 0; k < num_part; k++) {
        if (part[k].x == i && part[k].y == k) 
        {
          fprintf(fp, "+");
          found++;
          printf("O");
          break;
        }
      }
    
      if (!found) {
        fprintf(fp, " ");
        printf("X");
      }
    }
    //right border
    fprintf(fp, "*\n");
  }



  //bottom borcer
  for(int i = 0; i < COL + 2; i++) {
    fprintf(fp, "*");
  }
}

int main(int argc, char **argv)
{
  FILE *fp, *fp2;
  struct Point point[ROW * COL];
  fp = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "w");
  int sec = atoi(argv[3]);

  int part_n = 0;

  while (fscanf(fp, "%d,%d,%d,%d",
              &point[part_n].x, &point[part_n].y, &point[part_n].vx, &point[part_n].vy) != EOF) {
    part_n++;
  }

  colcheck(point, &part_n);
  move(fp2, point, sec, part_n);
  print(fp2, point, part_n);

  fclose(fp);
  fclose(fp2);
  return 0;
}