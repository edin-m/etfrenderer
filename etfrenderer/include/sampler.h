#ifndef SAMPLER_H
#define SAMPLER_H

#include <QImage>
#include <QPixmap>
#include <QPainter>

#include "types.h"

class Sampler
{
public:
    Sampler()
        : m_points(NULL),
          m_count(0),
          m_numPoints(0),
          m_name(QString("BasicSampler"))

    {
    }

    virtual ~Sampler()
    {
        if( m_numPoints > 0 && m_points != NULL )
            delete[] m_points;
    }

    /**
      Funkcija koja ucitava parametre iz proslijedjenog XMLa
      */
    //virtual bool loadFromXML(const QString& xml);

    /**
      Ova f-ja ce generisati tacke
      */
    virtual const vec2* generate(int num_samples) = 0;

    /**
      Points getter
      */
    virtual const vec2* points() const { return m_points; }

    /**
      number of points getter
      */
    unsigned num_points() const { return m_numPoints; }

    /**
      return next sample
      */
    virtual const vec2& sample() const
    {
        return m_points[m_count++ % m_numPoints];
    }

    /**
      sampler name
      */
    virtual QString name() const { return m_name; }

    /**
      print sampler values
      */
    virtual void testOutput() const
    {
        for(int i = 0; i < m_numPoints; i++)
        {
            qDebug() << sample();
        }
    }

    /**
      save output to image
      */
    virtual void testOutput(QImage& image) const
    {
        int width = image.width();
        int height = image.height();

        image.fill(Qt::white);
        for(int i = 0; i < m_numPoints; i++)
        {
            const vec2& _sample = sample();
            int x = _sample.x() * (width - 1);
            int y = _sample.y() * (height - 1);

//            QPainter painter;
//            painter.begin(&image);
//            painter.drawRect(QRect(1, 1, 3, 3));
//            painter.end();
            image.setPixel(x, y, rgb(0x000000));
        }
    }

protected:

    /**
      Kreator za tacke.
      */
    vec2* createPoints(int num_points)
    {
        if( m_points != NULL )
            delete[] m_points;

        m_points = new vec2[num_points];
        m_numPoints = num_points;
        return m_points;
    }

    mutable uint m_count;
    uint m_numPoints;
    vec2* m_points;
    QString m_name;
};

#endif // SAMPLER_H
