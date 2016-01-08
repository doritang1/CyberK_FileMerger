#include "ck_filemerger.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CK_FileMerger w;
    w.show();

    return a.exec();
}
