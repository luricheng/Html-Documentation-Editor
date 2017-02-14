#include "docker.h"
#include "ui_docker.h"

Docker::Docker(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Docker)
{
    ui->setupUi(this);
}

Docker::~Docker()
{
    delete ui;
}
