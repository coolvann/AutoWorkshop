#ifndef TIMESLOT_H
#define TIMESLOT_H
#include <QTime>
// ① 结构体
struct TimeSlot
{
    int index;        // 0 ~ 4
    QTime start;
    QTime end;
};
#endif // TIMESLOT_H
