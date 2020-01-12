#ifndef SHADER_H
#define SHADER_H

#include "types.h"
#include "structs.h"
#include "light.h"
#include "xmlutil.h"
#include "exception.h"

class Shader
{
public:
    Shader() :
        m_id(0) { }

    virtual ~Shader() {}

    unsigned id() const { return m_id; }

    /**
      Evaluates shader using ray, HitRecord result and one light.
      */
    virtual Color shade(const Ray&, const HitRecord&, const Light*) const = 0;

    /**
      TODO: make pure virtual
      */
    virtual Color shade(const Ray&, const HitRecord &) const
    {
        return Color("pink");
        //throw MethodNotImplemented();
    }

    /**
      Loads shader from XML string.
      Returns false or true if successful.
      */
    virtual bool loadFromXML(const QString& xml) = 0;

protected:
    // shader id
    unsigned m_id;

    /**
      Generates next ID
      */
    static unsigned nextID() { static unsigned ID = 10000; return ID++; }

    /**
      Loads id or generates one.
      */
    bool loadID(const QString& xml)
    {
        bool ok = false;
        unsigned _id = xmlutil::attr(xml, "id").trimmed().toUInt(&ok);

        m_id = ok ? _id : nextID();

        return ok;
    }
};

#endif // SHADER_H
