#ifndef RANDOMSAMPLER_H
#define RANDOMSAMPLER_H

#include "sampler.h"
#include "util/util.h"

class RandomSampler : public Sampler
{
public:
    RandomSampler()
    {
        m_name = QString("RandomSampler");
    }

    const vec2* generate(int num_samples)
    {
        m_numPoints = num_samples;
        createPoints(num_samples);

        for(uint i = 0; i < num_samples; i++)
        {
            vec2& _point = m_points[i];
            _point.setX( util::random(0, 100, 0.01f) );
            _point.setY( util::random(0, 100, 0.01f) );
        }

        return m_points;
    }
};

#endif // RANDOMSAMPLER_H
