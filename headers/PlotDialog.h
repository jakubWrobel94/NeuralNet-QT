#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(std::vector<double>& dataToPlot,QWidget *parent = 0);
    ~PlotDialog();

private:
    Ui::PlotDialog *ui;
    QVector<double> errorValues;
    QVector<double> epochArg;
};

#endif // PLOTDIALOG_H
