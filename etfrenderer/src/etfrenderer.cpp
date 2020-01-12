#include "etfrenderer.h"

Etfrenderer::Etfrenderer()
{
}

Sampler* Etfrenderer::createSampler(QString name) const
{
    Sampler* s = new RandomSampler;
    return s;
}
