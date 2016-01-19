#include "titleextract.h"
#include <QStringMatcher>
#include <QtCore>

QStringList* titleExtract(QString str)
{
    QString tokenBegin("<title>");
    QString tokenEnd("</title>");

    QStringMatcher matcher;
    QStringList* strlstTitles = new QStringList();

    int offsetTitleBegin = 0; //타이틀의 시작위치
    int offsetCurrent = 0; //찾을 위치

    for(;;)
    {
        matcher.setPattern(tokenBegin);

        /* offsetCurrent는 검색 시작위치 및 결과위치로,
         * 시작태그 검색완료후에는 시작태그의 시작위치로,
         * 종결태그 검색완료후에는 종결태그의 시작위치로,
         * 순환문의 끝에서는 첫번째 타이틀의 마지막으로 옮겨진다.*/

        /*만약 tokenBegin을 못만나면,즉 2번째 <title>이 없으면 matcher.indexIn()이 -1을 반환하므로
        반복문을 탈출한다.*/
        offsetCurrent = matcher.indexIn(str, offsetCurrent);

        if (offsetCurrent<0){

            break;

        } else {

            offsetTitleBegin = offsetCurrent + tokenBegin.length();

            matcher.setPattern(tokenEnd);
            offsetCurrent = matcher.indexIn(str, offsetCurrent);
            int titleLength = offsetCurrent - offsetTitleBegin;

            strlstTitles->append(str.mid(offsetTitleBegin,titleLength));
            offsetCurrent = offsetTitleBegin + titleLength; //첫번째 타이틀의 마지막으로 검색시작위치를 옮김
        }
    }

    return strlstTitles;
}
