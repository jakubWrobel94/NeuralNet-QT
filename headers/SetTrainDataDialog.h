#ifndef SETTRAINDATADIALOG_H
#define SETTRAINDATADIALOG_H

#include <QDialog>

namespace Ui {
class SetTrainDataDialog;
}

class SetTrainDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetTrainDataDialog(QWidget *parent = 0);
    ~SetTrainDataDialog();
public slots:
    void loadSamples();
    void loadTargets();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SetTrainDataDialog *ui;
    QString* samplesDirectory;
    QString* targetsDirectory;
};

#endif // SETTRAINDATADIALOG_H
