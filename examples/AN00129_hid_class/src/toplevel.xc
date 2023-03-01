#include <platform.h>

extern "C" {
    int main_tile0(chanend c_intertile);
    int main_tile1(chanend c_intertile);
}

int main(void)
{
    chan c_intertile;

    par {
        on tile[0]: main_tile0(c_intertile);
        on tile[1]: main_tile1(c_intertile);
    }
    return 0;
}