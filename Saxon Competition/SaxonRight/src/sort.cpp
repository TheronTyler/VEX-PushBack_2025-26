#include "robot-config.h"
#include "vex.h"



void sort() {
    bool threadRunning = true;
    while(threadRunning) {
        color_sort.setLightPower(100, pct);
        if (color_sort.color() == blue){
        motor_group(intakeupper, intakelower).stop();
        }
    }
}