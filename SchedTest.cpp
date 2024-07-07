#include <iostream>
#include "ScheduleMenu.h"
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
            // Edit
            break;
        case 4:
            // Delete
            break;
        case 0: 
            return 0;
            break;
        default:
            break;
        }
    }
}
