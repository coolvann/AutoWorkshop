#ifndef IUNSAVEDSTATE_H
#define IUNSAVEDSTATE_H
class IUnsavedState
{
public:
    virtual ~IUnsavedState() = default;
    virtual bool hasUnsavedChanges() const = 0;
    virtual void clearState() = 0;

};
#endif // IUNSAVEDSTATE_H
