#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Define the ccorrect date
char C[31][3][10];
const char Start[][10] = {"17", "Mar", "Fri"};

// Define the arry for result
char Cond[][10] = {"0"};
// char Result[][10] = {"0"};

// Define a two-dimensional array to represent the cells on the green paper
// Actual two-dimensional array, symbolic
const char *G[8][7] = {
    {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "#"},
    {"Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "#"},
    {"1", "2", "3", "4", "5", "6", "7"},
    {"8", "9", "10", "11", "12", "13", "14"},
    {"15", "16", "17", "18", "19", "20", "21"},
    {"22", "23", "24", "25", "26", "27", "28"},
    {"29", "30", "31", "Sun", "Mon", "Tue", "Wed"},
    {"#", "#", "#", "#", "Thu", "Fri", "Sat"}};
//  0->exept value， 1-> occupied, 2-> outside area
int T[8][7] = {
    0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 0, 0, 0

};

// Represents 10 blue graphic blocks
// Consider the case of rotation, the maximum range does not exceed 4*4
// 1 -> effective area, 0-> vacant area
int B0[4][4] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0};
int B1[4][4] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0};
int B2[4][4] = {
    1, 1, 1, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0};
int B3[4][4] = {
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0};
int B4[4][4] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0};
int B5[4][4] = {
    1, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};
int B6[4][4] = {
    1, 0, 0, 0,
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0};
int B7[4][4] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0};
int B8[4][4] = {
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0};
int B9[4][4] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1};

// Rotate the blue square
// 90 -> Rotate 90 degrees clockwise, 180, 270 same

void rotate(int input[4][4], int output[4][4], int angle)
{
    switch (angle)
    {
    case 90:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[j][3 - i] = input[i][j];
            }
        }
        break;
    case 180:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[3 - i][3 - j] = input[i][j];
            }
        }
        break;
    case 270:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                output[3 - j][i] = input[i][j];
            }
        }
        break;
    default:
        printf("Invalid angle. Please enter 90, 180, or 270.\n");
    }
}

// Define the rotated array
int B0_R[4][4], B1_R[4][4], B0_R[4][4], B0_R[4][4], B0_R[4][4],
    B0_R[4][4], B0_R[4][4], B0_R[4][4], B0_R[4][4], B0_R[4][4] = {0};

// input an 2dimantional array
void display(int array[][4], int rows, int columns)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

// place blocks and check
int place(int block[4][4], int row, int col)
{
    // Check if the block can be placed without overlapping with occupied positions or going outside the paper.
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] == 1)
            {
                int newRow = row + i;
                int newCol = col + j;

                if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 7)
                {
                    printf("Placement failed: outside of the paper.\n");
                    return -1;
                }

                if (T[newRow][newCol] != 0)
                {
                    printf("Placement failed: overlapping with occupied position.\n");
                    return -1;
                }
            }
        }
    }

    // Place the block.
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] == 1)
            {
                T[row + i][col + j] = 1;
            }
        }
    }

    return 1;
}

// According to the given date, initialize 31 dates in array C
void _init_C(const char start_date[][10])
{
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int current_day = atoi(start_date[0]);
    int current_month = 0;
    for (int i = 0; i < 12; i++)
    {
        if (strcmp(months[i], start_date[1]) == 0)
        {
            current_month = i;
            break;
        }
    }
    int current_weekday = 0;
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(days[i], start_date[2]) == 0)
        {
            current_weekday = i;
            break;
        }
    }

    for (int i = 0; i < 31; i++)
    {
        sprintf(C[i][0], "%02d", current_day);
        strcpy(C[i][1], months[current_month]);
        strcpy(C[i][2], days[current_weekday]);

        current_day++;
        if (current_day > days_in_month[current_month])
        {
            current_day = 1;
            current_month++;
            if (current_month >= 12)
            {
                break;
            }
        }
        current_weekday = (current_weekday + 1) % 7;

        if (i == 30 && current_month == 0)
        {
            break;
        }
    }
}

// valide the condition
void valid(int T[8][7], const char *G[8][7], char Cond[][10]) {
    int border_error = 0;
    int zeros_count = 0;
    int condition_error = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            if (T[i][j] == 2) {
                if (strcmp(G[i][j], "#") != 0) {
                    border_error = 1;
                }
            } else if (T[i][j] == 0) {
                zeros_count++;
                int found = 0;
                for (int k = 0; k < 3; k++) {
                    if (strcmp(G[i][j], Cond[k]) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    condition_error = 1;
                }
            }
        }
    }

    if (border_error) {
        printf("Border damaged, result invalid.\n");
    } else if (zeros_count != 3) {
        printf("Placement error, extra space.\n");
    } else if (condition_error) {
        printf("Does not satisfy the condition.\n");
    } else {
        printf("Congratulations!\n");
    }
}

int main(int argc, char *aegv[])
{
    // place the block
    int row = 2;
    int col = 1;

    if (place(B0, row, col))
    {
        printf("Placement succeeded.\n");
    }
    else
    {
        printf("Placement failed.\n");
    }

    // initialize 31 dates
    _init_C(Start);
    for (int i = 0; i < 31; i++)
    {
        printf("%s %s %s\n", C[i][0], C[i][1], C[i][2]);
    }

    // valide , check the result
    char Cond[][10] = {"17", "Mar", "Fri"};
    valid(T, G, Cond);

    return 0;
}
