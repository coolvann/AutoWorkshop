#include "BaseTab.h"
#include <QVBoxLayout>
BaseTab::BaseTab(QWidget* parent) : QWidget(parent)
{
    stack = new QStackedWidget(this);
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stack);
}

QStackedWidget* BaseTab::getStack() const
{
    return stack;
}
