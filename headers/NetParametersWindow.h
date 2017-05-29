#ifndef NETPARAMETERSWINDOW_H
#define NETPARAMETERSWINDOW_H


#include <QWidget>
#include "SetHiddenLayersDialog.h"
#include"CreateNetDialog.h"

namespace Ui {
class netParametersWindow;
}

class netParametersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit netParametersWindow(QWidget *parent = 0);
    ~netParametersWindow();

    std::vector<int>* hiddenLayersTopology;

private slots:
    void on_cancelButton_clicked();

    void on_setHiddenLayersbutton_clicked();

    void on_acceptButton_clicked();

private:
    Ui::netParametersWindow *ui;
};

#endif // NETPARAMETERSWINDOW_H
