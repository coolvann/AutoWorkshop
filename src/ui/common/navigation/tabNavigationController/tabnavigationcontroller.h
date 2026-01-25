#ifndef TABNAVIGATIONCONTROLLER_H
#define TABNAVIGATIONCONTROLLER_H
#include <QObject>
#include <QTabWidget>
#include <QStackedWidget>
/**
 * @brief To show the root page when a tab is click
 */
class TabNavigationController: public QObject
{
    Q_OBJECT
public:
    explicit TabNavigationController(QTabWidget* tabWidget, QObject* parent = nullptr);
    void registerTabs(int tabIndex, QStackedWidget* stack);
    void onTabChanged(int index);

private:
    QTabWidget* tabWidget;
    QMap<int, QStackedWidget*> tabStacks;
};

#endif // TABNAVIGATIONCONTROLLER_H
