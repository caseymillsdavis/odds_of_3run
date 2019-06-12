#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RUNS 1000000000ULL
#define DEAL_N 10

static int r(uint16_t max)
{
    int rem;
    int res;
    rem = RAND_MAX % max;
    do
    {
        res = rand();
    } while (res > (RAND_MAX - rem));
    return res % max;
}

static int check_is_in(int *d, int c, size_t n)
{
    unsigned i;
    for (i = 0; i < n; i++)
    {
        if (d[i] == c)
        {
            return 1;
        }
    }

    return 0;
}

static void deal_n(int *d, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++)
    {
        int c;

        do
        {
            c = r(52);
        } while (check_is_in(d, c, i));

        d[i] = c;
    }
}

static int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    return (arg1 > arg2) - (arg1 < arg2);
}

/* Input is a deck of size N. */
static int is_run(int *d, size_t n)
{
    unsigned i;

    qsort(d, n, sizeof(int), compare_ints);

    for (i = 0; i < (n - 2); i++)
    {
        if ((d[i+2] - d[i+1] == 1) &&
            (d[i+1] - d[i]   == 1))
        {
            /* Gotta handle 12, 25, 38. */
            if (!(d[i+1] == 12 || d[i+1] == 25 || d[i+1] == 38 ||
                  d[i+1] == 13 || d[i+1] == 26 || d[i+1] == 39))
            {
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    long unsigned count = 0;
    long unsigned successes = 0;

    srand(time(NULL));

    while (count++ < RUNS)
    {
        int d[DEAL_N];
        deal_n(d, DEAL_N);
        successes += is_run(d, DEAL_N);
    }

    printf("Run of three in %llu deals: %lu (%f)\n", RUNS, successes,
            (double)successes/RUNS);

    return 0;
}
