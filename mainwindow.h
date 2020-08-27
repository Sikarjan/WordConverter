#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QClipboard *clipboard;

    void toClipboard(const QString &text);

private slots:
    void on_pushButton_clicked();
    void on_wordInput_returnPressed();
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QString input;
    QString converted;
    QStringList words;
    QStringListModel *model;
};
#endif // MAINWINDOW_H
