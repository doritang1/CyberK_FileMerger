#ifndef CK_FILEMERGER_H
#define CK_FILEMERGER_H

#include <QDialog>

namespace Ui {
class CK_FileMerger;
}

class CK_FileMerger : public QDialog
{
    Q_OBJECT

public:
    explicit CK_FileMerger(QWidget *parent = 0);
    ~CK_FileMerger();

private slots:
    void on_btnTarget_clicked();

    void on_btnSource_clicked();

    void on_btnStart_clicked();

private:
    Ui::CK_FileMerger *ui;
    QStringList strlstSourcefileNames;
    QString targetfileName;
};

#endif // CK_FILEMERGER_H
