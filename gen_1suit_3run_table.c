#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint32_t v;

    printf("static uint16_t table_1suit_3_run[] =\n");
    printf("{\n");
    for (v = 0; v < 0x2000; v++)
    {
        int r = 0;
        if (((v & 0x1c00) == 0x1c00) ||
            ((v & 0x0e00) == 0x0e00) ||
            ((v & 0x0700) == 0x0700) ||
            ((v & 0x0380) == 0x0380) ||
            ((v & 0x01c0) == 0x01c0) ||
            ((v & 0x00e0) == 0x00e0) ||
            ((v & 0x0070) == 0x0070) ||
            ((v & 0x0038) == 0x0038) ||
            ((v & 0x001c) == 0x001c) ||
            ((v & 0x000e) == 0x000e) ||
            ((v & 0x0007) == 0x0007))
        {
            r = 1;
        }
        if (v % 16 == 0)
            printf("    ");
        printf("%d,", r);
        if ((v+1) % 16 == 0)
            printf("\n");
        else
            printf(" ");
    }
    printf("};\n");

    return 0;
}
