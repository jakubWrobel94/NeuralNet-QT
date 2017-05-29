#ifndef NEURONSETTINGSDIALOG_H
#define NEURONSETTINGSDIALOG_H

#include <QDialog>
#include"NetParametersWindow.h"
namespace Ui {
class NeuronSettingsDialog;
}

class NeuronSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeuronSettingsDialog(QWidget *parent = 0);
    ~NeuronSettingsDialog();

private slots:
    void plot();
    void on_pushButton_clicked();

private:
    Ui::NeuronSettingsDialog *ui;
};

#endif // NEURONSETTINGSDIALOG_H
