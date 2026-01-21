#ifndef ILEAVEGUARD_H
#define ILEAVEGUARD_H
class ILeaveGuard
{
public:
    virtual ~ILeaveGuard() = default;
    virtual bool canLeave() = 0;
    virtual void leaveAndClear() = 0;
};
#endif // ILEAVEGUARD_H
