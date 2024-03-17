#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1000

void insertion_sort(char **lines, int num_lines)
{
    for (int i = 1; i < num_lines; i++)
    {
        char temp[MAX_LINE_LEN];
        strcpy(temp, lines[i]);
        int j = i - 1;
        while (j >= 0)
        {
            char file1[MAX_LINE_LEN];
            char file2[MAX_LINE_LEN];

            strcpy(file1, lines[j]);
            strcpy(file2, temp);

            char *num1_str = file1;
            char *num2_str = file2;

            while (!isdigit(*num1_str))
                num1_str++;
            while (!isdigit(*num2_str))
                num2_str++;

            num1_str += strspn(num1_str, "0");
            num2_str += strspn(num2_str, "0");

            int num1 = atoi(num1_str);
            int num2 = atoi(num2_str);

            if (num1 > num2)
            {
                strcpy(lines[j + 1], lines[j]);
                j--;
            }
            else if (num1 < num2)
            {
                break;
            }
            else
            {
                int len1 = strlen(file1);
                int len2 = strlen(file2);

                if (len1 > len2)
                {
                    strcpy(lines[j + 1], lines[j]);
                    j--;
                }
                else if (len1 < len2)
                {
                    break;
                }
                else // if the lengths are the same
                {
                    int cmp = strncasecmp(file1, file2, len1);
                    if (cmp > 0)
                    {
                        strcpy(lines[j + 1], lines[j]);
                        j--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        strcpy(lines[j + 1], temp);
    }
}

void allocate_memory(char ***lines, int num_lines)
{
    *lines = malloc(num_lines * sizeof(char *));
    for (int i = 0; i < num_lines; i++)
    {
        (*lines)[i] = malloc(MAX_LINE_LEN * sizeof(char));
    }
}

void deallocate_lines(char **lines, int num_lines)
{
    for (int i = 0; i < num_lines; i++)
    {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char *argv[])
{

    char *input_file = argv[1];
    char *output_file = argv[2];

    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    int num_lines = 0;
    char buffer[MAX_LINE_LEN];

    while (fgets(buffer, MAX_LINE_LEN, input))
    {
        num_lines++;
    }

    char **lines;
    allocate_memory(&lines, num_lines);

    fseek(input, 0, SEEK_SET);

    for (int i = 0; i < num_lines; i++)
    {
        if (fgets(lines[i], MAX_LINE_LEN, input))
        {
            lines[i][strcspn(lines[i], "\n")] = 0;
        }
    }

    insertion_sort(lines, num_lines);

    for (int i = 0; i < num_lines; i++)
    {
        fprintf(output, "%s", lines[i]);
        if (i != num_lines - 1)
        {
            fprintf(output, "\n");
        }
    }

    deallocate_lines(lines, num_lines);

    fclose(input);
    fclose(output);

    return 0;
}