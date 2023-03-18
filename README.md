# Calendrier

[TOC]

## Context



### Decription

- An irregular green sheet with days 1-31, Monday to Sunday, January to December.

- Ten blue squares of different sizes and shapes, each square can be rotated

- Put all these squares on the green paper, and finally you can leave three positions, corresponding to the desired year, month, and day

  ### Purpose

Each group selects 31 dates and calculates each date as the target value

  - How many solutions totaly

  - How much time will it take

To understand the concept of algorithmic complexity

## Model the Problem

### variables

- Block placement  (G[8] [7])
- Block ID  (0 - 10)
- Block rotation angle  (0/90/180/270)

### parameter

- target date (ex. `Cond[][10] = {"17", "Mar", "Fri"}`)

### domain of values

- All possible scenarios that end up leaving only the target date

### constraints

`can_place`

- Block cannot cover target area
- Blocks cannot overlap
- Blocks cannot extend beyond green paper borders

## Methodology

- **C**

### Abstraction

It is very important to abstract real-life problems into abstract code problems

- Abstract the green paper into a three-dimensional array whose elements are strings  `char *G[8][7]`

  - Where there is content, it means the corresponding character
  - Compared with the array, the green paper is irregular, and the blank part is replaced by `#`

- In order to conveniently represent the state of each position, create a new integer array `int T[8][7]`

  - `0` means blank part
  - `1` indicates the part already occupied
  - `2` represents the irregular part, which is also the boundary
  - `3` indicates where the target date is located

- Abstraction of ten blue squares

  - Every block just like a arry 2D 

    ```c
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0}
    ```

  - A three-dimensional array representing the default state of all the block `int B[10][4][4]`

  - Another 3D array representing the rotated square`int B_R[10][4][4]`

- Abstraction of various operations

  - Initialization: 1 and 3 all become 0, and the place occupied by the target date becomes 3
    `void _init_T(char Cond[][10])`
  - Placement: Turn the place of 0 into 1  `void place(int id, int x, int y)`
  - Check: Cannot override 1 and 2 `bool can_place(int id, int x, int y)`
  - Pick up: the corresponding 1 becomes 0 `void unplace(int id, int x, int y)`
  - Confirmation: the number array corresponds to the string array, and the result is compared with the target value
    `void valid(int T[8][7], char Cond[][10])`

  ### Algorithm

  **Backtracking**

  - Rursive Function

  ```c
  void solve(int id, int *solutionCount)
  {
      if (id == 10)
      {
          (*solutionCount)++;
          return;
      }
  
      for (int i = 0; i < 8; i++)
      {
          for (int j = 0; j < 7; j++)
          {
              for (int k = 0; k < 4; k++)
              {
                  if (can_place(id, i, j))
                  {
                      place(id, i, j);
                      solve(id + 1, solutionCount);
                      unplace(id, i, j);
                  }
                  rotate(id);
              }
          }
      }
  }
  ```

  - Applicate in main

  ```c
  solve(0, &solutionCount);
  ```

  **Complexity**

  - The length of the running time to indicate the complexity

  ```c
  # include <time.h>
  
  // Get the begining time
  
          clock_t start = clock();
  
          solve(0, &solutionCount);
          
      
  // valide , check the result
          valid(T, Cond);
  
  // Get the ending time
          clock_t end = clock();
  
  // Calculate the time taken for this iteration
          double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
  
          printf("Time taken for %dth day: %f seconds\n", day + 1, time_taken);
  ```

  ### Others

  Here are some innovative points

  - The initialization of 31 dates is done automatically

  ```c
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
  ```

  ```c
  // Just change the start date
  const char Start[][10] = {"17", "Mar", "Fri"};
  _init_C(Start);
  ```

  

  - The calculation results of 31 dates are completed at one timeHere are some innovative points

  ```c
  for (int day = 0; day < 31; day++)
      {
  
          for (int index = 0; index < 3; index++)
          {
              for (int s = 0; s < 10; s++)
              {
                  Cond[index][s] = C[day][index][s];
              }
              printf("%s", Cond[index]);
          }
          printf("\n");
  
          _init_T(Cond);
  
          // Get the begining time
          clock_t start = clock();
  
          solve(0, &solutionCount);
          
      
          // valide , check the result
          valid(T, Cond);
  
          // Get the ending time
          clock_t end = clock();
  
          // Calculate the time taken for this iteration
          double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
  
          printf("Time taken for %dth day: %f seconds\n", day + 1, time_taken);
          printf("Total solutions: %d\n", solutionCount);
      }
  ```

  

## Result



|  ID  | month | calendar | day  | #solutions | sconde CPU |
| :--: | :---: | :------: | :--: | :--------: | :--------: |
|  1   |   3   |    17    |  5   |     3      | 40.639000  |
|  2   |   3   |    18    |  6   |     5      | 55.347000  |
|  3   |   3   |    19    |  7   |     5      | 30.561000  |
|  4   |   3   |    20    |  1   |     7      | 29.109000  |
|  5   |   3   |    21    |  2   |     9      | 42.183000  |
|  6   |   3   |    22    |  3   |     11     | 68.586000  |
|  7   |   3   |    23    |  4   |     19     | 54.239000  |
|  8   |   3   |    24    |  5   |     21     | 45.692000  |
|  9   |   3   |    25    |  6   |     21     | 50.100000  |
|  10  |   3   |    26    |  7   |     21     | 24.724000  |
|  11  |   3   |    27    |  1   |     21     | 15.285000  |
|  12  |   3   |    28    |  2   |     27     | 33.198000  |
|  13  |   3   |    29    |  3   |     38     | 88.537000  |
|  14  |   3   |    30    |  4   |            | 70.790000  |
|  15  |   3   |    31    |  5   |            | 45.193000  |
|  16  |   4   |    1     |  6   |            | 15.076000  |
|  17  |   4   |    2     |  7   |            | 27.108000  |
|  18  |   4   |    3     |  1   |            | 12.908000  |
|  19  |   4   |    4     |  2   |            | 11.986000  |
|  20  |   4   |    5     |  3   |            | 21.979000  |
|  21  |   4   |    6     |  4   |            | 21.937000  |
|  22  |   4   |    7     |  5   |            | 13.385000  |
|  23  |   4   |    8     |  6   |            | 14.651000  |
|  24  |   4   |    9     |  7   |            | 27.030000  |
|  25  |   4   |    10    |  1   |            | 14.623000  |
|  26  |   4   |    11    |  2   |            | 23.054000  |
|  27  |   4   |    12    |  3   |            | 21.958000  |
|  28  |   4   |    13    |  4   |    2947    | 28.924000  |
|  29  |   4   |    14    |  5   |    2949    | 62.915000  |
|  30  |   4   |    15    |  6   |    2973    | 86.653000  |
|  31  |   4   |    16    |  7   |    2975    | 34.363000  |
