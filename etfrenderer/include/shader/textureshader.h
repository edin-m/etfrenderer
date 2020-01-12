#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H

#include "types.h"
#include "structs.h"
#include "shader.h"

class TextureShader : public Shader
{
public:
    virtual ~TextureShader() {}

    virtual bool loadFromXML(const QString& xml) = 0;
protected:

};

#endif
