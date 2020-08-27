#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    model = new QStringListModel();
    clipboard = QApplication::clipboard();

    ui->setupUi(this);
    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toClipboard(const QString &text)
{
    clipboard->setText(text, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(text, QClipboard::Selection);
    }

    #if defined(Q_OS_LINUX)
        QThread::msleep(1); //workaround for copied text not being available...
    #endif

    ui->statusbar->showMessage(tr("Copied ")+text+tr(" to clipboard."), 3000);
}


void MainWindow::on_pushButton_clicked()
{
    input = ui->wordInput->text();
    if(input.isEmpty()){
        return;
    }

    converted = "";

    for (int i=0;i<input.length();i++) {
        QString mChar = input.at(i);

        if(mChar == " "){
            mChar = "_";
        }else if (mChar == "ä") {
            mChar = "a0";
        }else if (mChar == "ö") {
            mChar = "o0";
        }else if (mChar == "ü") {
            mChar = "u0";
        }else if (mChar == "?") {
            mChar = "QUERY";
        }else if (mChar == ":") {
            mChar = "COLON";
        }else if (mChar == ".") {
            mChar = "DOT";
        }else if (mChar == "'") {
            mChar = "UPDOT";
        }else if (mChar == "(") {
            mChar = "LEFT_BRACE";
        }else if (mChar == ")") {
            mChar = "RIGHT_BRACE";
        }else if (mChar == "/") {
            mChar = "AND";
        }else if (mChar == "@") {
            mChar = "AT_0";
        }else if (mChar == ",") {
            mChar = "COMMA";
        }else if (mChar == "-") {
            mChar = "SLINE";
        }else if (mChar == "<") {
            mChar = "SHIFT_LEFT";
            i++;
        }else if (mChar == ">") {
            mChar = "SHIFT_RIGHT";
            i++;
        }else if (mChar == ";") {
            mChar = "SEPERATE";
        }

        converted = converted+"_"+mChar+"_, ";
    }

    converted = converted+"_END_,";

    words.insert(0, converted);
    model->setStringList(words);
    ui->wordInput->clear();

    toClipboard(converted);
}

void MainWindow::on_wordInput_returnPressed()
{
    ui->pushButton->clicked();
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QString text = model->data(index).toString();
    toClipboard(text);
}
