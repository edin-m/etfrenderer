#ifndef EMDOBJECT_H
#define EMDOBJECT_H

#include <algorithm>

#include <QString>
#include <QFile>
#include <QDebug>

#include "types.h"
#include "structs.h"

#include "shape/triangleshape.h"
#include "util/bbox.h"

namespace
{
struct face
{
    uint fa1, fa2, fa3;

    virtual ~face() {}
};

struct face2 : face
{
    uint fb1, fb2, fb3;

    virtual ~face2() {}
};

struct face3 : face2
{
    uint fc1, fc2, fc3;

    virtual ~face3() {}
};
}

class EmdObject
{
    /**

      identifikacija formata face-ova
      */
    enum FaceFormat { F_V, F_VVT, F_VVTVN, F_VVN };

//    struct emd_header
//    {
//        FaceFormat faceFormat;
//        char start_index;
//        vec3 absolute_center;
//        QString coordinates;
//    };

    /**
      konverzija stringa u faceformat
      */
    FaceFormat Str2FaceFormat(const QString&);

    /**
      ciste i kreiraju nove nizove
      */
    vec3* createVertices(int count);
    vec2* createTexels(int count);
    vec3* createNormals(int count);
    face* createFaces(int count);

    /**
      cita face u zavisnosti od faceFormata i smijesta u _face
      */
    void readFace(QTextStream& in, face* _face);

    void readHeader(QTextStream& in);

    void loadVertices(QTextStream& in);
    void loadTexels(QTextStream& in);
    void loadNormals(QTextStream& in);
    void loadFaces(QTextStream& in);

    face& faces_index(uint index) const;
public:

    EmdObject();
    ~EmdObject();

    bool hit(const Ray& in_ray, HitRecord& result, bool isShadowRay = false) const;
    const vec3& center() const;

    void loadFromStream(QTextStream& stream);
    void loadFromFile(const QString& filename);

    bool isLoaded() { return m_isloaded; }
    void generateBoundingBox();

    void testOutput();
private:

    // array of vertices
    vec3* vertices;

    // array of normals
    vec3* normals;

    // array of texels
    vec2* texels;

    // array of faces
    face* faces;

    // object center point
    vec3 m_center;

    // number of vertices
    int vertices_count;

    // number of normals
    int normals_count;

    // number of texels
    int texels_count;

    // number of faces
    int faces_count;

    // face storage format (face, face & texel, face & normal, all three)
    FaceFormat faceFormat;

    // index at which faces start indexing (1 for obj-like file)
    short startIndex;

    // is it loaded
    bool m_isloaded;

    // are vertex coordinates relative to m_center
    bool m_isrelative;

    // bounding box for this object
    BoundingBox* bbox;
};

#endif // EMDOBJECT_H
