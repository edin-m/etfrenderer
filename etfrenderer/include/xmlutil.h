#ifndef XMLUTIL_H
#define XMLUTIL_H

#include <QXmlQuery>
#include <QStringList>

#include <QDebug>

#include "types.h"
#include "color.h"

namespace xmlutil
{

    /** Converts xml ('<any x="1" y="2.2" z="3.3" />') to vec3 */
    vec3 xml2vec3(const QString& xml);

    /** Returns map of attributes extracted from xml
      using xpath /\*\/@attributeName/data(.) */
    QMap<QString, QString> attrs(const QString& xml, const QStringList& attrs);

    /** Returns attributeName attribute data from XML */
    QString attr(const QString& xml, const QString& attributeName);

    /** Returns evaluated xpath query from xml */
    QString evaluate(const QString& xml, const QString& xpath);

    /** Counts number of occurances of node in xpath */
    uint count(QXmlQuery& query, const QString& xpath);

    /** XML to Color u stilovima:
        <boja1 r="1.0" g="0.0" b="0.0" a="0.0" />
        <boja2 color_name="red" />
        <boja3 color_name="#ff0000" />
    */
    Color color(const QString& xml, Color fail_color = Color());
}

#endif // XMLUTIL_H
