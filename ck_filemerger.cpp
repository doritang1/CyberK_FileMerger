#include "ck_filemerger.h"
#include "ui_ck_filemerger.h"
#include "manipulate.h"
#include <QtWidgets>

CK_FileMerger::CK_FileMerger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CK_FileMerger)
{
    ui->setupUi(this);
}

CK_FileMerger::~CK_FileMerger()
{
    delete ui;
}

void CK_FileMerger::on_btnTarget_clicked()
{
    targetfileName = QFileDialog::getSaveFileName(this, tr("Select Target"), "../../dictionary_v63/SKKU_German_6.3", "HTML (*.htm)");
    ui->lineTarget->setText(targetfileName);
}

void CK_FileMerger::on_btnSource_clicked()
{   //상대경로 사용
    strlstSourcefileNames = QFileDialog::getOpenFileNames(this, tr("Select Source"), "../../dictionary_v63/SKKU_German_6.3", "HTML (*.htm)");
    QFile sourcefile(this);

    //자바스타일 이터레이터 선언
    QStringListIterator itr(strlstSourcefileNames);
    while (itr.hasNext())
    {
        sourcefile.setFileName(itr.next().toLocal8Bit().constData());

        if(sourcefile.open(QFile::ReadOnly|QFile::Text))
        {
            //title을 뽑아내고 변환을 위해 엔터키를 정리하는 함수 manipulate
            QString strManipulated
                    = manipulate(QString::fromLocal8Bit(sourcefile.readAll()));//한글사용을 위해 fromLocal8Bit함수 사용


            ui->txtSource->appendPlainText(strManipulated);

            ui->lineSource->setText(sourcefile.fileName());
            ui->lstSource->addItem(sourcefile.fileName());
        }
        sourcefile.close();
    }
}

void CK_FileMerger::on_btnStart_clicked()
{
    QFile targetfile(ui->lineTarget->text());
    targetfile.open(QIODevice::WriteOnly);
    targetfile.write(ui->txtSource->toPlainText().toUtf8()+"\n");//utf-8로 저장함
    //파일에 쓰는 다른 방법(근데 실제로는 utf-8로 저장이 안된다.)
    //QTextStream out(&targetfile);
    //out<<ui->txtSource->toPlainText().toUtf8();//utf-8로 저장함
    targetfile.close();
}