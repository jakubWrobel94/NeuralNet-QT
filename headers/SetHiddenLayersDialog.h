#ifndef SETHIDDENLAYERSDIALOG_H
#define SETHIDDENLAYERSDIALOG_H

#include <QDialog>
#include"NetParametersWindow.h"
#include<QPlainTextEdit>
#include<QPair>
#include<QLabel>
#include<QLineEdit>
namespace Ui {
class setHiddenLayersDialog;
}

class setHiddenLayersDialog : public QDialog
{
    Q_OBJECT

public:

    explicit setHiddenLayersDialog(QWidget *parent = 0);
    explicit setHiddenLayersDialog(int hiddenLayers, QWidget *parent = 0);

    ~setHiddenLayersDialog();

private slots:

    void on_acceptButton_clicked();

private:

    Ui::setHiddenLayersDialog *ui;
    int hiddenLayersNumber;
    QWidget* widget;
    QVector<QLabel*> labels;
    QVector<QLineEdit*> textBoxes;
};

#endif // SETHIDDENLAYERSDIALOG_H
