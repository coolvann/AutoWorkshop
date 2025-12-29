#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui/windows/login/LoginWidget.h"
#include "ui/windows/createAccount/CreateAccountWidget.h"
#include "app/AppContext.h"
#include <QStackedLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageLoginSignup);

    // create a stackedwidget with parent logInUpHolder ***注意designer里logInUpHolder不能有任何布局,否则stack布局无效***
    auto loginupStack = new QStackedLayout(ui->logInUpHolder);
    // crate a login widget
    auto loginWidget = new LoginWidget(ui->logInUpHolder);
    // create a create account widget
    auto createAccountWidget = new CreateAccountWidget(ui->logInUpHolder);

    loginupStack->addWidget(loginWidget); // index0
    loginupStack->addWidget(createAccountWidget); // index1
    loginupStack->setCurrentWidget(loginWidget);
    // switch to create accoutn widget
    connect(loginWidget, &LoginWidget::switchToCreateAccountWidget, this, [loginupStack, createAccountWidget](){
        loginupStack->setCurrentWidget(createAccountWidget);
        qDebug() << "Switched to createAccountWidget.";
    });

    // switch to login widget
    connect(createAccountWidget, &CreateAccountWidget::switchToLoginWidget, this, [loginupStack, loginWidget](){
        loginupStack->setCurrentWidget(loginWidget);
         qDebug() << "Switched to loginWidget.";
    });

    // on success login, switch to main page: load all tabs; show main page -> schedule
    connect(loginWidget, &LoginWidget::loginSuccess, this, [this](const std::optional<UserSession>& session){
        AppContext::instance().setSession(session);
        loadAllTabs();
        setFirstTabPage();
        ui->stackedWidget->setCurrentWidget(ui->pageMain);

    });



    // tickets->reload();
}

void MainWindow::loadAllTabs()
{
    ui->tabWidget->clear();   // 清空Designer自带的 page
    scheduleTab = new ScheduleTabWidget(AppContext::instance().getTicketService(), ui->tabWidget);
    ui->tabWidget->addTab(scheduleTab, "Schedule");

}

void MainWindow::setFirstTabPage()
{
    ui->tabWidget->setCurrentWidget(scheduleTab);
}


MainWindow::~MainWindow()
{
    delete ui;
}



