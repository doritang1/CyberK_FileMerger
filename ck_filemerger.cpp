#include "ck_filemerger.h"
#include "ui_ck_filemerger.h"
#include "titleextract.h"
#include "bodyextract.h"
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

}

void CK_FileMerger::on_btnStart_clicked()
{
    QFile sourcefile(this);

    QFile targetfile(ui->lineTarget->text());
    targetfile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&targetfile);
    out.setCodec("UTF-8");

    //자바스타일 이터레이터 선언
    QStringListIterator itrFiles(strlstSourcefileNames);
    while (itrFiles.hasNext())
    {
        sourcefile.setFileName(itrFiles.next().toLocal8Bit().constData());
        ui->lstSource->addItem(sourcefile.fileName());

        if(sourcefile.open(QFile::ReadOnly|QFile::Text))
        {
            //한글사용을 위해 fromLocal8Bit함수 사용
            QString text = QString::fromLocal8Bit(sourcefile.readAll());
            //엔터키 정리
            text = text.simplified();
            //title list를 뽑아내는 함수 titleExtract()
            QStringList* strlstTitles;
            strlstTitles = titleExtract(text);
            //body list를 뽑아내는 함수 bodyExtract(), 나중에 <header>...</header>는 제거한다.
            QStringList* strlstBodies;
            strlstBodies = bodyExtract(text);

            for(int i=0; i<strlstTitles->length();++i)
            {
                QString txt = strlstTitles->at(i);

                if(!txt.isEmpty()){

                    ui->txtSource->setPlainText(txt+" is being processed.");
                    out<<txt<<"\t"<<strlstBodies->at(1)<<"\n";
                    ui->txtSource->appendPlainText(txt+" is compiled over.");
                }
            }
            ui->lineSource->setText(sourcefile.fileName());
        }
        sourcefile.close();

    }
    //ui->txtSource->appendPlainText("\r\n");
    out<<"\n";
    targetfile.close();
}
