#include <iostream>
#include "src\ScheduleMenu.h"
using namespace std;

int main() {
    Schedule sched;
    while (true) {
        switch (sched.ScheduleMenu()) {
        case 1:
            sched.AddScheduleData();
            break;
        case 2:
            sched.ViewSchedule();
            break;
        case 3:
            sched.EditSchedule();
            break;
        case 4:
            sched.DeleteSchedule();
            break;
        case 0: 
            return 0;
            break;
        default:
            break;
        }
    }
}
