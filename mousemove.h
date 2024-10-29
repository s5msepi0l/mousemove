#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <cmath>

//totally didn't copy from stackoverflow
int count_digits(int n) {
    if (n == 0) return 1;
    return static_cast<int>(std::floor(std::log10(std::abs(n)))) + 1;
}

void mousemove(int x_pos, int y_pos) {
    static char command[] = "xdotool\0";
    static char argument[] = "mousemove\0";

    // i may be stupid :))
    char *x = new char[count_digits(x_pos)];
    strcpy(x, std::to_string(x_pos).c_str());
    

    char *y = new char[count_digits(y_pos)];
    strcpy(y, std::to_string(y_pos).c_str());

    std::to_string(x_pos).c_str();

    char *args[] = {command, argument, x, y, nullptr};
    execvp(command, args);
}