#include "tabnavigationcontroller.h"

TabNavigationController::TabNavigationController(QTabWidget* tabWidget, QObject* parent)
    :QObject(parent)
    , tabWidget(tabWidget)
{
    connect(tabWidget, &QTabWidget::currentChanged,
            this, &TabNavigationController::onTabChanged);

}

void TabNavigationController::registerTabs(int tabIndex, QStackedWidget* stack)
{
    tabStacks[tabIndex] = stack;
}


void TabNavigationController::onTabChanged(int index)
{
    qDebug() << "currentChanged index =" << index;
    qDebug() << "registered keys =" << tabStacks.keys();
    if (tabStacks.contains(index))
    {
        tabStacks[index]->setCurrentIndex(0);
    }
}
