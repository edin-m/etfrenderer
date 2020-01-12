#include "xmlutil.h"

vec3 xmlutil::xml2vec3(const QString& xml)
{
    QStringList list;
    list.append("x");
    list.append("y");
    list.append("z");

    QMap<QString, QString> map = xmlutil::attrs(xml, list);

    vec3 vec;

    vec.setX( map["x"].toFloat() );
    vec.setY( map["y"].toFloat() );
    vec.setZ( map["z"].toFloat() );

    return vec;
}

QMap<QString, QString> xmlutil::attrs(const QString& xml, const QStringList& attrs)
{
    QMap<QString, QString> map;
    QXmlQuery query;

    query.setFocus(xml);

    foreach( const QString& attr, attrs )
    {
        // data(.) xpath function extracts content from current result
        QString xpath = "/*/@" + attr + "/data(.)";
        QString evaluateTo;

        query.setQuery(xpath);
        query.evaluateTo(&evaluateTo);

        map.insert(attr, evaluateTo.trimmed());
    }

    return map;
}

QString xmlutil::attr(const QString& xml, const QString& attributeName)
{
    QXmlQuery query;
    QString evaluateTo;

    query.setFocus(xml);
    query.setQuery(QString("/*/@" + attributeName + "/data(.)"));

    bool result = query.evaluateTo(&evaluateTo);

    if( result )
        return evaluateTo.trimmed();
    else
        return "";
}

QString xmlutil::evaluate(const QString& xml, const QString& xpath)
{
    QXmlQuery query;
    QString evaluateTo;

    query.setFocus(xml);
    query.setQuery(xpath);

    bool result = query.evaluateTo(&evaluateTo);

    if( result )
        return evaluateTo.trimmed();
    else
        return "";
}

uint xmlutil::count(QXmlQuery& query, const QString& xpath)
{
    QString _xpath;

    if( xpath.trimmed().right(2) != "/*" )
        _xpath = xpath + "/*";
    else
        _xpath = xpath;

    QString evaluateTo;

    query.setQuery("count(" + _xpath + ")");
    query.evaluateTo(&evaluateTo);

    uint _count;
    bool ok;

    _count = evaluateTo.toUInt(&ok);

    if( !ok )
        return 0;

    return _count;
}

Color xmlutil::color(const QString& xml, Color fail_color)
{
    QXmlQuery query;
    query.setFocus(xml);

    QString r, g, b, a;

    query.setQuery("//@r/data(.)");
    query.evaluateTo(&r);

    query.setQuery("//@g/data(.)");
    query.evaluateTo(&g);

    query.setQuery("//@b/data(.)");
    query.evaluateTo(&b);

    query.setQuery("//@a/data(.)");
    query.evaluateTo(&a);

    float fr, fg, fb, fa;
    bool okr, okg, okb, oka;

    fr = r.toFloat(&okr);
    fg = g.toFloat(&okg);
    fb = b.toFloat(&okb);

    fa = a.toFloat(&oka);
    fa = oka ? fa : 1.0f;

    if( okr && okg && okb )
        return Color(fr, fg, fb, fa);

    // vadjenje iz color_name atributa
    QString name;

    query.setQuery("//@rgb/data(.)");
    if( query.evaluateTo(&name) )
    {
        QColor qcolor(name.trimmed());
        if( qcolor.isValid() )
            return Color(qcolor);
    }

    query.setQuery("//@color_name/data(.)");
    if( query.evaluateTo(&name) )
    {
        QColor qcolor(name.trimmed());
        if( qcolor.isValid() )
            return Color(qcolor);
    }

    return Color(fail_color);
}
