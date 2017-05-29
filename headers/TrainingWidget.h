#ifndef TRAININGWIDGET_H
#define TRAININGWIDGET_H

#include <QWidget>
class BackPropObserver;
namespace Ui {
class TrainingWidget;
}

class TrainingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingWidget(QWidget *parent = 0);
    ~TrainingWidget();

private slots:
    void on_pushButton_clicked();

    void on_plotButton_clicked();

private:
    Ui::TrainingWidget *ui;
    BackPropObserver* observer;
    bool firstTraining;

};

#endif // TRAININGWIDGET_H
