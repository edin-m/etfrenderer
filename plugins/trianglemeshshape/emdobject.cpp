#include "emdobject.h"

EmdObject::EmdObject()
    :
      vertices_count(0),
      texels_count(0),
      normals_count(0),
      vertices(NULL),
      texels(NULL),
      normals(NULL),
      faces_count(0),
      startIndex(0),
      faceFormat(F_VVT),
      m_isloaded(false),
      bbox(NULL),
      m_isrelative(false),
      m_center(vec3(0, 0, 0))
{
}

EmdObject::~EmdObject()
{
    if( vertices_count > 0 && vertices != NULL )
    {
        delete[] vertices;
    }

    if( texels_count > 0 && texels != NULL )
    {
        delete[] texels;
    }

    if( faces_count > 0 )
    {
        delete[] faces;
    }
}

/**
  Konvertuje string u FaceFormat enum
  v     => F_V
  vvt   => F_VVT
  vvn   => F_VVN
  vvtvn => F_VVTVN
*/
EmdObject::FaceFormat EmdObject::Str2FaceFormat(const QString& _str)
{
    if( _str == "v" )
    {
        return F_V;
    }

    if( _str == "vvt" )
    {
        return F_VVT;
    }

    if( _str == "vvtvn" )
    {
        return F_VVTVN;
    }

    if( _str == "vvn" )
    {
        return F_VVN;
    }

    return F_VVTVN;
}

vec3* EmdObject::createVertices(int count)
{
    if( vertices_count > 0 && vertices != NULL )
    {
        delete[] vertices;
    }

    vertices = new vec3[count];
    return vertices;
}

vec2* EmdObject::createTexels(int count)
{
    if( texels_count > 0 && texels != NULL )
    {
        delete[] texels;
    }

    texels = new vec2[count];
    return texels;
}

vec3* EmdObject::createNormals(int count)
{
    if( normals_count > 0 && normals != NULL )
    {
        delete[] normals;
    }

    normals = new vec3[count];
    return normals;
}

/**
  Zavisno od faceFormata kreiramo razlicite nizove za faces atribut
  */
face* EmdObject::createFaces(int count)
{
    if( faces_count > 0 && faces != NULL )
    {
        delete[] faces;
    }

    switch(faceFormat)
    {
        case F_V:
            faces = new face[count];
        break;
        case F_VVT:
        case F_VVN:
            faces = new face2[count];
        break;
        case F_VVTVN:
            faces = new face3[count];
        break;
    }

    return faces;
}

/**
  Funkcija koja vraca face& na osnovu indexa iz faces privatne varijable
  zato sto je face nadklasa za face2 i face3 pa ako faces pokazuje na face3 niz
  onda faces[] nece dati zeljeni clan niza.

  Zavisno od faces tipa treba se vratiti clan niza.
  */
face& EmdObject::faces_index(uint index) const
{
    switch(faceFormat)
    {
        case F_V:
        {
            return faces[index];
        }
        break;
        case F_VVT:
        case F_VVN:
        {
            face2* _f2 = (face2*) faces;
            return _f2[index];
        }
        break;
        case F_VVTVN:
        {
            face3* _f3 = (face3*) faces;
            return _f3[index];
        }
        break;
    }
}

/**
  Hit test za ovaj objekat.
  */
bool EmdObject::hit(const Ray& in_ray, HitRecord& result, bool isShadowRay) const
{
    // if exists, bounding box hit test
    if( bbox != NULL && !bbox->hit(in_ray) )
        return false;

    double d = 1e100;

    bool res = false;
    int index = -1;
    HitRecord tmpResult;

    // svaki face se provjerava hit testom sa TriangleShape::hitStatic()
    for(uint i = 0; i < faces_count; i++)
    {
        face& _face = faces_index(i);

        const vec3& v0 = vertices[_face.fa1];
        const vec3& v1 = vertices[_face.fa2];
        const vec3& v2 = vertices[_face.fa3];

        bool r = TriangleShape::hitStatic(v0, v1, v2, in_ray, tmpResult, isShadowRay, true);
        if( r && tmpResult.t < d )
        {
            result = tmpResult;
            d = result.t;
            res = true;
            index = i;
//            result.normal = vec3::normal(v0, v1, v2);
        }
    }

    // ne trebaju dalji prorcuni za shadow ray
    if( isShadowRay )
        return res;

    if( res && index >= 0 )
    {
        const vec3& v0 = vertices[ faces_index((uint)index).fa1 ];
        const vec3& v1 = vertices[ faces_index((uint)index).fa2 ];
        const vec3& v2 = vertices[ faces_index((uint)index).fa3 ];

        result.normal = vec3::normal(v0, v1, v2);

        if( faceFormat == F_VVT || faceFormat == F_VVTVN )
        {
            face2* _f2 = (face2*) faces;

            const vec2& t0 = texels[ _f2[index].fb1 ];
            const vec2& t1 = texels[ _f2[index].fb2 ];
            const vec2& t2 = texels[ _f2[index].fb3 ];

            // modifikovanje uv koordinata na osnovu texela
            vec2 uv = result.uv;
            vec2 t01 = (t1 - t0) * uv.x();
            vec2 t02 = (t2 - t0) * uv.y();

            vec2 _uv = t0 + t01 + t02;
            result.uv = _uv;
        }
    }

    return res;
}

const vec3& EmdObject::center() const
{
    return m_center;
}

/**
  U zavisnosti od zapisa formata face-a tako se i treba procitati.

  moguci nacini:
    v -  index vertexa
    vt - index texela
    vn - index normale

  Po uzoru na .obj format:
    vn mogu biti izostavljeni
    vt mogu biti izostavljeni ali tada (ako ima vn) stoji v//vn

  Primjer:
    #1: f v v v
    #2: f v/vt v/vt v/vt
    #3: f v//vn v//vn v//vn
    #4: f v/vt/vn v/vt/vn v/vt/vn

  Napomena: treba testirati sve ove slucajeve
  */
void EmdObject::readFace(QTextStream& in, face *_face)
{
    QString str;
    char c;

    int f1, f2, f3;
    if( faceFormat == F_V )
    {
        in >> str >> f1 >> f2 >> f3;
        _face->fa1 = f1 - startIndex;
        _face->fa2 = f2 - startIndex;
        _face->fa3 = f3 - startIndex;

        return;
    }

    int t1, t2, t3;
    if( faceFormat == F_VVT || faceFormat == F_VVN )
    {
        // v/vt
        if( faceFormat == F_VVT )
        {
            in >> str
               >> f1 >> c >> t1
               >> f2 >> c >> t2
               >> f3 >> c >> t3;
        }
        // v//vn
        else if( faceFormat == F_VVN )
        {
            in >> str
               >> f1 >> c >> c >> t1
               >> f2 >> c >> c >> t2
               >> f3 >> c >> c >> t3;
        }

        face2* _f2 = (face2*) _face;

        _f2->fa1 = f1 - startIndex;
        _f2->fa2 = f2 - startIndex;
        _f2->fa3 = f3 - startIndex;

        _f2->fb1 = t1 - startIndex;
        _f2->fb2 = t2 - startIndex;
        _f2->fb3 = t3 - startIndex;

        return;
    }

    int n1, n2, n3;
    // v/vt/vn
    if( faceFormat == F_VVTVN )
    {
        in >> str
           >> f1 >> c >> t1 >> c >> n1
           >> f2 >> c >> t2 >> c >> n2
           >> f3 >> c >> t3 >> c >> n3;

        face3* _f3 = (face3*) _face;

        _f3->fa1 = f1 - startIndex;
        _f3->fa2 = f2 - startIndex;
        _f3->fa3 = f3 - startIndex;

        _f3->fb1 = t1 - startIndex;
        _f3->fb2 = t2 - startIndex;
        _f3->fb3 = t3 - startIndex;

        _f3->fc1 = n1 - startIndex;
        _f3->fc2 = n2 - startIndex;
        _f3->fc3 = n3 - startIndex;

        return;
    }

}

void EmdObject::readHeader(QTextStream& in)
{
    QString str;
    in >> str;

    if( str.toLower() == "header-start" )
    {
        while(!in.atEnd())
        {
            in >> str;
            str = str.toLower();

            if( str == "header-end" )
            {
                return;
            }

            if( str == "face_format" )
            {
                in >> str;
                faceFormat = EmdObject::Str2FaceFormat(str);
            }

            if( str == "start_index" )
            {
                in >> startIndex;
            }

            if( str == "absolute_center" )
            {
                float x, y, z;
                in >> x >> y >> z;
                m_center = vec3(x, y, z);
            }

            if( str == "coordinates" )
            {
                in >> str;
                if( str.toLower() == "relative" )
                    m_isrelative = true;
            }
        }
    }
}

void EmdObject::loadVertices(QTextStream& in)
{
    QString str;
    in >> str;

    if( str.toLower() == "vertices" )
    {
        int _count = 0;
        in >> _count;

        if( _count <= 0 )
        {
            return;
        }

        vertices = createVertices(_count);
        vertices_count = _count;

        for(int i = 0; i < vertices_count; i++)
        {
            float x, y, z;

            in >> str >> x >> y >> z;
            vec3 tmp(x, y, z);

            if( m_isrelative )
                tmp = tmp + m_center;

            vertices[i] = tmp;
        }
    }

}

/**
  Citanje texela koji su pohranjeni u formatu (treci je opcionalan)
  vt # # [#]
*/
void EmdObject::loadTexels(QTextStream& in)
{
    QString str;
    in >> str;

    if( str == "texels" )
    {
        int _count = 0;
        in >> _count;

        if( _count <= 0 )
        {
            return;
        }

        texels = createTexels(_count);
        texels_count = _count;

        for(int i = 0; i < texels_count; i++)
        {
            float u, v, w;
            in >> str >> u >> v >> w;

            texels[i].setX(u);
            texels[i].setY(v);
        }

    }
}


/**
  Ucitavanje normala koje su pohranjene u formatu
  vn # # #
*/
void EmdObject::loadNormals(QTextStream &in)
{
    QString str;
    in >> str;

    if( str == "_normals" )
    {
        int _count = 0;
        in >> _count;
        if( _count <= 0 )
            return;

        normals = createNormals(_count);
        normals_count = _count;

        for(uint i = 0; i < normals_count; i++)
        {
            float b, t, n;
            in >> str >> b >> t >> n;

            normals[i].setX(b);
            normals[i].setY(t);
            normals[i].setZ(n);
        }
    }
}

void EmdObject::loadFaces(QTextStream& in)
{
    QString str;
    in >> str;

    if( str.toLower() == "faces" )
    {
        int _count = 0;
        in >> _count;

        if( _count <= 0 )
        {
            return;
        }

        faces = createFaces(_count);
        faces_count = _count;

        for(int i = 0; i < faces_count; i++)
        {
            // ovaj dio do readFace() treba zbog odabira
            // prave adrese koja je drugacija zbog naslijedjivanja

            face* _chosenOne = &faces[i];
            if( faceFormat == F_V )
            {
                _chosenOne = (face*)(faces + i);
            }
            else if( faceFormat == F_VVT || faceFormat == F_VVN )
            {
//              _chosenOne = &((face2*)faces)[i];
                _chosenOne = (face*)(((face2*)faces) + i);
            }
            else if( faceFormat == F_VVTVN )
            {
                _chosenOne = (face*)(((face3*)faces) + i);
            }

            readFace(in, _chosenOne);
        }
    }

//    qDebug() << "Loaded " << faces_count << " texels:";
//    for(int i = 0; i < faces_count; i++)
//    {
//        face2* _f2 = (face2*) (((face2*)faces) + i);
//        qDebug() << _f2->fa1 << "/" << _f2->fb1 << " "
//                 << _f2->fa2 << "/" << _f2->fb2 << " "
//                 << _f2->fa3 << "/" << _f2->fb3;
    //    }
}

void EmdObject::loadFromStream(QTextStream& stream)
{
    while( !stream.atEnd() )
    {
        readHeader(stream);
        loadVertices(stream);

        if( faceFormat ==  F_VVT || faceFormat == F_VVTVN )
        {
            loadTexels(stream);
        }

        if( faceFormat == F_VVN || faceFormat == F_VVTVN )
        {
            loadNormals(stream);
        }

        loadFaces(stream);
    }

    qDebug() << "header-start";
    qDebug() << "face_format "      << faceFormat;
    qDebug() << "start_index"       << startIndex;
    qDebug() << "absolute_center"   << m_center;
    qDebug() << "header-end";

    qDebug()
        << "Read " << vertices_count    << " vertices.\n"
        << "Read " << texels_count      << " texels.\n"
        << "Read " << faces_count       << " faces.\n";

    qDebug() << "Sizeof:" << vertices_count * (vertices == NULL ? 0 : sizeof( vertices[0]   ))
                          << texels_count   * (texels   == NULL ? 0 : sizeof( texels[0]     ))
                          << faces_count    * (normals  == NULL ? 0 : sizeof( faces[0]      ));

    m_isloaded = true;
}

void EmdObject::loadFromFile(const QString &filename)
{
    QFile file(filename);

    if( file.open(QIODevice::ReadOnly) )
    {
        QTextStream in(&file);

        qDebug() << "EMD file " << filename << " reading.\n";
        loadFromStream(in);

        testOutput();
        file.close();
    }
    else
    {
        qDebug() << "FILE NOT READ: " << filename;
    }

}

void EmdObject::generateBoundingBox()
{
    if( bbox != NULL )
        delete bbox;

    if( vertices_count <= 2 )
        return;

    vec3& v0 = vertices[0];
    vec3& v1 = vertices[1];

    bbox = new BoundingBox(v0, v1);

    for(unsigned i = 2; i < vertices_count; i++)
    {
        vec3& vec = vertices[i];
        bbox->append(vec);
    }

    qDebug() << "New bounding box has: " <<
                bbox->p0 << bbox->p1;
}

void EmdObject::testOutput()
{
    qDebug() << "header-start";
    qDebug() << "face_format " << faceFormat;
    qDebug() << "start_index" << startIndex;
    qDebug() << "header-end";

    qDebug() << "vertices " << vertices_count;
    for(int i = 0; i < vertices_count; i++)
    {
        qDebug() << "v " << vertices[i];
    }

    qDebug() << "texels " << texels_count;
    for(int i = 0; i < texels_count; i++)
    {
        qDebug() << "vt " << texels[i];
    }

    qDebug() << "normals " << normals_count;
    for(int i = 0; i < normals_count; i++)
    {
        qDebug() << "vn " << normals[i];
    }

    qDebug() << "faces " << faces_count;
    for(int i = 0; i < faces_count; i++)
    {
        if( faceFormat == F_V )
        {

            face* _f = (faces + i);
            qDebug() << "f "
                     << _f->fa1 << " "
                     << _f->fa2 << " "
                     << _f->fa3;
        }
        else if( faceFormat == F_VVN || faceFormat == F_VVT )
        {
            face2* _f2 = (face2*)(((face2*)faces) + i);
            qDebug() << "f "
                     << _f2->fa1 << "/" << _f2->fb1 << " "
                     << _f2->fa2 << "/" << _f2->fb2 << " "
                     << _f2->fa3 << "/" << _f2->fb3;
        }
        else if( faceFormat == F_VVTVN )
        {

            face3* _f3 = (face3*)(((face3*)faces) + i);
            qDebug() << "f "
                     << _f3->fa1 << "/" << _f3->fb1 << "/" << _f3->fc1 << " "
                     << _f3->fa2 << "/" << _f3->fb2 << "/" << _f3->fc2 << " "
                     << _f3->fa3 << "/" << _f3->fb3 << "/" << _f3->fc3 ;
        }
    }

}

