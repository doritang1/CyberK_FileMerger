#include "bodyextract.h"

QStringList* bodyExtract(QString str)
{
    static QStringList strlstBodies;
    strlstBodies = str.split("</head>");
//    strlstBodies.replaceInStrings("&auml;", "ä");
//    strlstBodies.replaceInStrings("&ouml;", "ö");
//    strlstBodies.replaceInStrings("&uuml;", "ü");

    return &strlstBodies;
}

