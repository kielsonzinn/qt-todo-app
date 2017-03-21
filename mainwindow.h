#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>

#include "task.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow( QWidget* parent = NULL );
    ~MainWindow();

public:
    void updateStatus();

public slots:
    void addTask();
    void removeTask( Task* task );
    void taskStatusChanged( Task* task );

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;

};

#endif // MAINWINDOW_H
