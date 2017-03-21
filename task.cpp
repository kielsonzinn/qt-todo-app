#include "task.h"
#include "ui_task.h"

#include <QDebug>
#include <QInputDialog>

Task::Task( const QString& name, QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::Task )
{
    ui->setupUi( this );

    setName( name );

    connect( ui->editButton, &QPushButton::clicked, this, &Task::rename );

    connect( ui->removeButton, &QPushButton::clicked, [this, name] {
        qDebug() << "Trying to remove" << name;

        this->emit removed( this );
    });

    connect( ui->checkBox, &QCheckBox::toggled, this, &Task::checked );
}

Task::~Task() {
    delete ui;
}

void Task::setName( const QString& name ) {
    ui->checkBox->setText( name );
}

QString Task::name() const {
    return ui->checkBox->text();
}

bool Task::isCompleted() const {
    return ui->checkBox->isChecked();
}

void Task::rename() {
    bool isOkeey = false;

    QString value = QInputDialog::getText( this, tr( "Edit task" ), tr( "Task name" ),
                                           QLineEdit::Normal, this->name(), &isOkeey );

    if ( isOkeey && !value.isEmpty() ) {
        setName( value );
    }

}

void Task::checked( bool isChecked ) {
    QFont qFont( ui->checkBox->font() );
    qFont.setStrikeOut( isChecked );
    ui->checkBox->setFont( qFont );

    emit statusChanged( this );
}
