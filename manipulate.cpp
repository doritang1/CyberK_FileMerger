#include <manipulate.h>
#include <QStringMatcher>
#include <QStringList>
#include <QtCore>
QString manipulate(QString str)
{
    str.remove("\n");
    //QStringList words = str.split("\r\n");
    //str = words.join("\n");

    QString tokenBegin("<title>");
    QString tokenEnd("</title>");

    QStringMatcher matcher;
    QStringList strlstTitles;
    int offset = 0;//검색 시작위치

    for(;;)
    {
        //qDebug()<<"오프셋:"+QString::number(offset)+"\n";
        matcher.setPattern(tokenBegin);

        /*offset은 검색 시작위치로 첫번째 타이틀 검색시에는 0이고,
        두번째 타이틀 검색시에는 첫번째 타이틀의 마지막이다.*/

        /*만약 token을 못만나면,즉 2번째 타이틀이 없으면 matcher.indexIn()이 -1을 반환하므로
        반복문을 탈출한다.*/
        offset = matcher.indexIn(str,offset);
        if (offset<0) break;

        int indexTitleBegin = offset + tokenBegin.length();

        offset = indexTitleBegin;

        matcher.setPattern(tokenEnd);
        int indexTitleLength = matcher.indexIn(str,offset)-indexTitleBegin;
        qDebug()<<"길이:"+QString::number(indexTitleLength)+"\n";
        strlstTitles.append(str.mid(indexTitleBegin,indexTitleLength));
        offset += indexTitleLength; //첫번째 타이틀의 마지막으로 검색시작위치를 옮김
    }

    if(strlstTitles.length()<2) //만약 2번째 타이틀이 없다면 첫번째 타이틀에 그냥 탭을 넣어준다.
    {
        str = strlstTitles.at(0)+ "\t" + str + "\n";
    } else if(strlstTitles.at(1).isEmpty()){ //만약 2번째 타이틀이 있다면 두번째 타이틀에 움라우트표시로 *를 넣고 탭을 넣어준다.
        str = strlstTitles.at(0)+ "\t" + str + "\n";
    } else {
        str = strlstTitles.at(1)+("*\t") + str + "\n";
    }

    return str;
}
