#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QApplication>
#include <QInputDialog>

MainWindow::MainWindow( QWidget* parent) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    connect( ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask );

    updateStatus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateStatus() {
    int completedCount = 0;

    for ( auto t : mTasks ) {
        if ( t->isCompleted() ) {
            completedCount++;
        }
    }

    int todoCount = mTasks.size() - completedCount;

    ui->statusLabel->setText( QString( "Status: %1 todo / %2 completed" ).arg( todoCount ).arg( completedCount ) );
}

void MainWindow::addTask() {
    bool isOkey = false;

    QString name = QInputDialog::getText( this, tr( "Add task" ), tr( "Task name" ),
                                          QLineEdit::Normal, tr( "Untitled task" ), &isOkey );

    if ( isOkey && !name.isEmpty() ) {
        qDebug() << "Adding new task";

        Task* task = new Task( name );
        mTasks.append( task );

        ui->tasksLayout->addWidget( task );

        connect( task, &Task::removed, this, &MainWindow::removeTask );

        updateStatus();
    }
}

void MainWindow::removeTask( Task* task ) {
    mTasks.removeOne( task );

    ui->tasksLayout->removeWidget( task );
    task->setParent( NULL );

    delete task;

    updateStatus();
}

void MainWindow::taskStatusChanged( Task* task ) {
    Q_UNUSED( task );

    updateStatus();
}
