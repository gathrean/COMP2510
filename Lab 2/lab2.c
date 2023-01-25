#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARRAY_SIZE 20 // do NOT touch

void rotateArray(char *ptr, int n) {

    // "bin"
    char temp[20][20];
    char temp2[20][20];

    if (n == 0 || n == 360){
        for(int i = 0; i < ARRAY_SIZE; i++){
            for(int j = 0; j < ARRAY_SIZE; j++) {
            }
            // no change
        }
    }

    if (n == 90 || n == -270){
        // 1. Copies the input.txt file into a 20x20 array called "temp".
        for(int i = 0; i < ARRAY_SIZE; i++){
            for(int j = 0; j < ARRAY_SIZE; j++){
                temp[i][j] = *ptr; // Puts the value of element's value that ptr is pointing to, to temp array.
                ptr++; // next will be [i][j+1]
            }
        }

        // 2. Transposes the copied array into a second copy array.
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                temp2[j][ARRAY_SIZE - 1 - i] = temp[i][j]; // Transposes temp1 into temp2.
            }
        }

        // 3. "Resets" the pointer back to [0][0]
        ptr -= 400;

        // 4. Flip temp2 horizontally.
        for (int i = 0; i < ARRAY_SIZE; i++){
            for (int j = 0; j < ARRAY_SIZE; j++){
                *ptr = temp2[i][j];
                ptr++;
            }
        }
    }

    if (n == 180 || n == -180) {

        // 1. Copies the input.txt file into a 20x20 array called "temp".
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                temp[i][j] = *ptr; // Puts the value of element's value that ptr is pointing to, to temp array.
                ptr++; // next will be [i][j+1]
            }
        }

        // 2. Copies temp2 array (no transpose).
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                temp2[i][j] = temp[i][j];
            }
        }

        // 3. "Resets" the pointer back to [0][0]
        ptr -= 400;

        // 4. Flip temp2 vertically.
        for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
            for (int j = ARRAY_SIZE - 1; j >= 0; j--) {
                *ptr = temp2[i][j];
                ptr++;
            }
        }

    }

    if (n == 270 || n == -90){

        // 1. Copies the input.txt file into a 20x20 array called "temp".
        for(int i = 0; i < ARRAY_SIZE; i++){
            for(int j = 0; j < ARRAY_SIZE; j++){
                temp[i][j] = *ptr; // Puts the value of element's value that ptr is pointing to, to temp array.
                ptr++; // next will be [i][j+1]
            }
        }

        // 2. Transposes the copied array into a second copy array.
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                temp2[i][j] = temp[j][ARRAY_SIZE - 1 - i]; // Transposes temp1 into temp2.
            }
        }

        // 3. "Resets" the pointer back to [0][0]
        ptr -= 400;

        // 4. Flip temp2 horizontally.
        for (int i = 0; i < ARRAY_SIZE; i++){
            for (int j = 0; j < ARRAY_SIZE; j++){
                *ptr = temp2[i][j];
                ptr++;
            }
        }
    }

}

/*********************************/
// Do NOT touch anything below this line
int main(int argc, char **argv){
  FILE *fp;
  int i = 0, j, n;
  char c;
  char arr[20][20];

  fp = fopen(argv[1], "r");
  n = atoi(argv[2]);

  do{
    c = (char)fgetc(fp);
    if(isprint(c) != 0){
      arr[i/ARRAY_SIZE][i%ARRAY_SIZE] = c;
      i++;
    }
  } while(c != EOF);


  printf("========INPUT=======\n");
  for(i = 0; i < ARRAY_SIZE; i++){
      for(j = 0; j < ARRAY_SIZE; j++){
	printf("%c", arr[i][j]);
      }
      printf("\n");
  }
  
  rotateArray(&arr[0][0], n);

  printf("=======OUTPUT=======\n");
  for(i = 0; i < ARRAY_SIZE; i++){
      for(j = 0; j < ARRAY_SIZE; j++){
	printf("%c", arr[i][j]);
      }
      printf("\n");
  }
  
  fclose(fp);
  return 0;
}

