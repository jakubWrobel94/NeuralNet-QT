#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"CreateNetDialog.h"
#include"NetParameters.h"
#include"Net.h"

class TrainingWidget;
class BackPropagation;
class SetTrainDataDialog;
class TrainingData;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    NetParameters netParameters;

    void createNet();
    void createTrainingData(QString &samplesPath,QString &targetsPath);
    void createBackPropagation();
    void setNetInfo();
    Ui::MainWindow * getUi();

    BackPropagation *getBackPropagation();
public slots:
    void createNewNetWindow();
    void createSetTrainDataDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SetTrainDataDialog* setTrainDataDialog;
    Net* net;
    TrainingData* data;
    BackPropagation* backpropagation;
    TrainingWidget* trainingWidget;
};

#endif // MAINWINDOW_H
