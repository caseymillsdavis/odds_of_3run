#include <stdio.h>
#include <stdint.h>

#include "table_1suit_3run.h"

#define MAX_V 0x10000000000000ULL
#define GOAL  0x10000000000000ULL
#define DEAL 10

static int run_check(uint64_t v)
{
    uint16_t s0, s1, s2, s3;

    s0 = v & 0x1FFF;
    s1 = (v >> 13) & 0x1FFF;
    s2 = (v >> 26) & 0x1FFF;
    s3 = (v >> 39) & 0x1FFF;
    return table_1suit_3_run[s0] ||
           table_1suit_3_run[s1] ||
           table_1suit_3_run[s2] ||
           table_1suit_3_run[s3];
}

int main(void)
{
    uint64_t v = 0;
    uint64_t idx = 0;
    uint64_t run_count = 0;

    while (v < MAX_V)
    {
        int pc = __builtin_popcountll(v);

        if (pc == DEAL)
        {
            int tz;

            if (run_check(v))
                run_count++;
            
            tz = __builtin_ctzll(v);
            v += 1ULL << tz;
            idx++;
        }
        else
        {
             v++;
        }
    }

    printf("count %lu with %lu runs in %llu\n", idx, run_count, MAX_V);

    return 0;
}
