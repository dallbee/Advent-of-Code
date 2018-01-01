#include <stdlib.h>
#include <klib/kvec.h>
#include <sds/sds.h>
#include <string.h>
#include <tgmath.h>
#include "../common.h"

sds solve_03_a(sdsvec input) {
    int num = atoi(kv_A(input, 0));

    // Reach nearest perfect square
    int i;
    for (i = 1; i*i < num; i += 2);

    // Find distances based on pivots
    int d;
    for (int j = 0; j < 4; ++j) {
        int pivot = i*i - j*(i-1);
        d = abs(pivot - num);
        if (d <= (i-1) / 2) {
            return sdsfromlonglong(i-1-d);
        }
    }

    return NULL;
}

void update_grid(size_t n, uint64_t grid[n][n], size_t* pos, int* vec, int val) {
    grid[pos[0]][pos[1]] = val;
    pos[0] += vec[0];
    pos[1] += vec[1];
}

uint64_t sum_grid(size_t n, uint64_t grid[n][n], size_t* pos) {
    uint64_t sum = 0;
    sum += grid[pos[0] + 1][pos[1] - 1];
    sum += grid[pos[0] + 1][pos[1] + 0];
    sum += grid[pos[0] + 1][pos[1] + 1];
    sum += grid[pos[0] + 0][pos[1] - 1];
    sum += grid[pos[0] + 0][pos[1] + 1];
    sum += grid[pos[0] - 1][pos[1] - 1];
    sum += grid[pos[0] - 1][pos[1] + 0];
    sum += grid[pos[0] - 1][pos[1] + 1];
    return sum;
}

/**
 * Regression fit on the sequence yields 11.33e^0.177x
 * Guessing a lower bound of 10e^0.1x:
 *  x = 10*log(y/10)
 */
sds solve_03_b(sdsvec input) {
    int num = atoi(kv_A(input, 0));

    long double squares = 10 * log(num / 10.0);
    uint64_t length = (uint64_t) ceil(sqrt(squares));

    // Make sure we're at an even square
    length += length % 2;

    size_t pos[2] = { length/2, length/2 };
    size_t dir = 0;
    int seq[4][2] = {
        {  0,  1 },
        {  1,  0 },
        {  0, -1 },
        { -1,  0 },
    };

    uint64_t grid[length][length];
    memset(grid, 0, length * length * sizeof(**grid));

    // initialize center square
    update_grid(length, grid, pos, seq[dir++], 1);

    int64_t sum = 0;
    while (sum < num) {
        sum = sum_grid(length, grid, pos);

        // attempt to turn
        int* vec = seq[(dir + 1) % 4];
        if (grid[pos[0] + vec[0]][pos[1] + vec[1]] == 0) {
            dir = (dir + 1) % 4;
        }

        update_grid(length, grid, pos, seq[dir], sum);
    }

    return sdsfromlonglong(sum);
}
