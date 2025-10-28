#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Qfile"
#include "QStandardPaths"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\toDoFile.txt");

    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);


    while(!in.atEnd()){
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\toDoFile.txt");

    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream out(&file);


    for (int i = 0; i < ui->listWidget->count(); ++i) {
        out<<ui->listWidget->item(i)->text()<<"\n";
    }

    file.close();


}

void MainWindow::on_addBtn_clicked()
{
    QString taskText = ui->txtTask->text().trimmed();

    if (taskText.isEmpty()) {
        QMessageBox::information(this, "Aviso", "Preencha a caixa com algum caractere antes de adicionar.");
        return;
    }

    QListWidgetItem* item = new QListWidgetItem(taskText, ui->listWidget);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);

    ui->txtTask->clear();
    ui->txtTask->setFocus();
}

void MainWindow::on_removeBtn_clicked()
{
      QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;

      for (QListWidgetItem* item : selectedItems) {
          delete ui->listWidget->takeItem(ui->listWidget->row(item));
      }
}


void MainWindow::on_removeAllBtn_clicked()
{
    ui->listWidget->clear();
}

