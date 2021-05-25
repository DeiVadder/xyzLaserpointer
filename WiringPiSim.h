#ifndef WIRINGPISIM_H
#define WIRINGPISIM_H

namespace WiringPi {

enum PinMode : int {
    INPUT,
    OUTPUT
};
enum WriteValue : int {
    LOW = 0,
    HIGH = 1
};

    static int const wiringPiSetupGpio()  {return 0;}
    static void const pinMode(int pin, int mode) {}
    static void const digitalWrite(int pin, int value) {}

}

#endif // WIRINGPISIM_H
