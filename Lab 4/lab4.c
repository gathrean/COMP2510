/**
 * Lab 4. Particle Simulator.
 *
 * In this lab, we will write a program that will
 * show as the location of particles after a
 * designated number of seconds.
 *
 * Requirements:
 * - XY grid is 20 by 20 √
 * - Particles will only move within this boundary. √
 * - The grid is boxed by borders. √
 * - The vertices of the borders are (-1,-1), (-1,21), (21,-1), and (21,21).
 * - The unit of velocity is 1 unit per second.
 * - This program will simulate movement and output the final position in the output file.
 * - Border must be marked with * symbols, particles with +.
 *
 * @author Gathrean (Ean) Dela Cruz, A01167248
 * @author Heeho (Max) Ryou,         A01322487
 * @return 0 int
 */

/**
 * Missing:
 * particles bouncing off the border as described in the instructions.
 * It also does not take into account that particles moving at a 45-degree angle 
 * will reflect their angle after bouncing off the border.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 20
#define COLS 20

struct particle
{
    int x;
    int y;
    int x_velocity;
    int y_velocity;
};

// Prints the particles in the output file
void printParticles(FILE *output_file, struct particle particles[], int num_particles)
{

    /************ PRINTS TOP BORDER ************/
    for (int j = 0; j < COLS + 2; j++)
    {
        fprintf(output_file, "*");
    }
    fprintf(output_file, "\n");

    for (int i = ROWS - 1; i >= 0; i--)
    {

        /************ PRINTS LEFT BORDER ************/
        fprintf(output_file, "*");

        // Searches output.txt if there is a particle or not
        for (int j = 0; j < COLS; j++)
        {
            int particle_found = 0;

            // Looks for the particles
            for (int k = 0; k < num_particles; k++)
            {
                // checks if there is a particle in the current position
                if (particles[k].x == j && particles[k].y == i)
                {
                    // fprintf(output_file, "%*c", COLS / 2 - particles[k].x, '+');
                    fprintf(output_file, "+");
                    particle_found++;
                    break;
                }
            }

            // Prints empty space if there is no particle in the current position
            if (!particle_found)
            {
                fprintf(output_file, " ");
            }
        }

        /************ PRINTS RIGHT BORDER ************/
        fprintf(output_file, "*\n");
    }

    /************ PRINTS BOTTOM BORDER ************/
    for (int j = 0; j < COLS + 2; j++)
    {
        fprintf(output_file, "*");
    }
}

int main(int argc, char *argv[])
{

    // Declares variables
    int num_particles = 0;
    char line[100];
    struct particle particles[100];

    // Checks if there are 4 arguments
    if (argc != 4)
    {
        printf("Please provide ./a.out input.txt output.txt <seconds>\n");
        return 1;
    }

    // Looks for input.txt, output.txt and number of seconds from argument values
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");
    int num_sec = atoi(argv[3]);

    // read the values of each particle
    while (fscanf(input_file, "%d,%d,%d,%d",
                  &particles[num_particles].x,
                  &particles[num_particles].y,
                  &particles[num_particles].x_velocity,
                  &particles[num_particles].y_velocity) != EOF)
    {
        num_particles++;
    }

    // move the particles and print the output
    for (int sec = 0; sec < num_sec; sec++)
    {
        // goes through each particle and moves them according to their velocity
        for (int i = 0; i < num_particles; i++)
        {
            particles[i].x += particles[i].x_velocity;
            particles[i].y += particles[i].y_velocity;

            // deals with particle X being negative, turns it to 0
            if (particles[i].x < 0)
            {
                particles[i].x = -1;
                particles[i].x_velocity = -particles[i].x_velocity;
            }
            // if particle X goes out of column, make it so the particle is just before the edge
            else if (particles[i].x >= COLS)
            {
                particles[i].x = COLS - 1;
                particles[i].x_velocity = -particles[i].x_velocity;
            }

            // deals with particles Y being negative, makes it 0
            if (particles[i].y < 0)
            {
                particles[i].y = -1;
                particles[i].y_velocity = -particles[i].y_velocity;
            }
            // if particle Y goes out of column, make it so the particle is just before the edge
            else if (particles[i].y >= ROWS)
            {
                particles[i].y = ROWS - 1;
                particles[i].y_velocity = -particles[i].y_velocity;
            }
        }
    }

    printParticles(output_file, particles, num_particles);

    fclose(input_file);
    fclose(output_file);
    return 0;
}