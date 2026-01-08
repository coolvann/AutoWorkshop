#ifndef CREATETICKETWIDGET_H
#define CREATETICKETWIDGET_H

#include <QWidget>

namespace Ui {
class CreateTicketWidget;
}

class CreateTicketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTicketWidget(QWidget *parent = nullptr);
    ~CreateTicketWidget();

private:
    Ui::CreateTicketWidget *ui;
};

#endif // CREATETICKETWIDGET_H
