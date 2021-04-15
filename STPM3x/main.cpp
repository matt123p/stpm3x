// STPM3x.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "stpm3x.h"

int main()
{
    Stpm3x pm(3);

    // Reset the power monitoring
    pm.sw_reset();

    // Now configure (default configuration is the Eval board)
    STPM_Configuration config;
    config.secondary_channel.ks = 2.4f/1000.0f;
    config.secondary_channel.Ai = 2;
    pm.configure(config);

    for (;;)
    {
        float primary_v, primary_i, secondary_v, secondary_i;
        pm.read_rms(primary_v, primary_i, secondary_v, secondary_i);

        std::cout << primary_v << "," << primary_i << "," << secondary_v << "," << secondary_i << std::endl;

        Sleep(1000);
    }
}


