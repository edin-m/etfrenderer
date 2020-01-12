#ifndef TESTINTERPOLATION_H
#define TESTINTERPOLATION_H

#include <QDebug>
#include <QtTest/QtTest>

#include "util/interpolation.h"

class TestInterpolation : public QObject
{
    Q_OBJECT
public:
    void testLinearInterpolation();
};

#endif // TESTINTERPOLATION_H
