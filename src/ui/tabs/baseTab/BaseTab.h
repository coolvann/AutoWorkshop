#ifndef BASETAB_H
#define BASETAB_H
#include <QWidget>
#include <QStackedWidget>
class BaseTab: public QWidget
{
    Q_OBJECT
public:
    explicit BaseTab(QWidget* parent = nullptr);
    QStackedWidget* getStack() const;

protected:
    QStackedWidget* stack;
};

#endif // BASETAB_H
