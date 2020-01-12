#define _NO_USE_QVEC
#include "softwarerenderer.h"

SoftwareRenderer::SoftwareRenderer()
{
}

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

template <typename T>
T min3(T a, T b, T c)
{
    return std::min(a, std::min(b, c));
}

template <typename T>
T max3(T a, T b, T c)
{
    return std::max(a, std::max(b, c));
}

struct Point2D {
    int x, y;
};

static FrameBuffer* _fb;

int orient2d(const Point2D& a, const Point2D& b, const Point2D& c)
{
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

void renderPixel(Point2D p, glm::vec3& uvw)
{
    _fb->set(p.x, p.y, rgb(0xff00aabb));
}

void drawTri(const Point2D& v0, const Point2D& v1, const Point2D& v2)
{
    // Compute triangle bounding box
    int minX = min3(v0.x, v1.x, v2.x);
    int minY = min3(v0.y, v1.y, v2.y);
    int maxX = max3(v0.x, v1.x, v2.x);
    int maxY = max3(v0.y, v1.y, v2.y);

    // Clip against screen bounds
    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, 500 - 1);
    maxY = std::min(maxY, 500 - 1);

    // Rasterize
    Point2D p;
    for (p.y = minY; p.y <= maxY; p.y++) {
        for (p.x = minX; p.x <= maxX; p.x++) {
            // Determine barycentric coordinates
            int w0 = orient2d(v1, v2, p);
            int w1 = orient2d(v2, v0, p);
            int w2 = orient2d(v0, v1, p);

            // If p is on or inside all edges, render pixel.
            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
                renderPixel(p, glm::vec3(w0, w1, w2));
        }
    }
}

Color fragmentShader()
{
    return Color(rgb(0xff0000ff));
}

glm::vec4 vertexShader(const glm::mat4& mvp, const glm::vec4& vertex)
{
    glm::vec4 out = mvp * vertex;
    out /= out.w;

    return out;
}

QDebug& operator<<(QDebug& out, glm::mat4& mat)
{
    out << "glm::mat4 \n"
            << mat[0][0] << mat[0][1] << mat[0][2] << mat[0][3] << "\n"
            << mat[1][0] << mat[1][1] << mat[1][2] << mat[1][3] << "\n"
            << mat[2][0] << mat[2][1] << mat[2][2] << mat[2][3] << "\n"
            << mat[3][0] << mat[3][1] << mat[3][2] << mat[3][3] << "\n"
               ;

    return out;
}

QDebug& operator<<(QDebug& out, glm::mat3& mat)
{
    out << "glm::mat3 \n"
            << mat[0][0] << mat[0][1] << mat[0][2]<< "\n"
            << mat[1][0] << mat[1][1] << mat[1][2]<< "\n"
            << mat[2][0] << mat[2][1] << mat[2][2]<< "\n"
               ;

    return out;
}

float sign(Point2D& p1, Point2D& p2, Point2D& p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(Point2D& pt, Point2D& v1, Point2D& v2, Point2D& v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}

#include <QPainter>

bool SoftwareRenderer::render(const FrameBuffer *framebuffer,
                              const QPoint &start,
                              const QSize &render_size)

{

    _fb = (FrameBuffer*)framebuffer;

    float vertices[] = {
        0.f, 0.f, 0.f, 1.0f,
        10.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 10.0f, 0.0f, 1.0f
    };

    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -40),
                                 glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));

    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.01f, 10000.0f);

    glm::mat4 mvp = projection * view;

    int x = 0;
    int y = 0;
    int width = 500;
    int height = 500;
    glm::vec4 viewport(x, y, width, height);
    glm::mat3 mat(1.0f);
    mat[0][0] = width / 2;
    mat[0][2] = width / 2 + x;
    mat[1][1] = height / 2;
    mat[1][2] = height / 2 + y;
//    mat = glm::transpose(mat);

    qDebug() << mat;

    float* vert = new float[3*2];
    for(int i = 0; i < 3; i++)
    {
        glm::vec4 vertex = glm::vec4(vertices[i*4 + 0],
                                     vertices[i*4 + 1],
                                     vertices[i*4 + 2],
                                     vertices[i*4 + 3]);

        glm::vec4 v = vertexShader(mvp, vertex);
//        glm::vec4 v = glm::project(glm::vec3(vertex.x, vertex.y, vertex.z),
//                                 glm::mat4(1.0f),
//                                 mvp,
//                                 glm::detail::tvec4<float>(0.0f, 0.0f, 500.0f, 500.0f));
        v+= 1.0f;



        glm::vec3 v3 = mat * glm::vec3(v.x, v.y, v.z);


        vert[i*2 + 0] = v3.x;
        vert[i*2 + 1] = v3.y;
//        vert[i*3 + 2] = v3.z;
//        vert[i*4 + 3] = v.w;

//        qDebug() << i << "(" << v.x << v.y << v.z << v.w << ")";
        qDebug() << i << "(" << v3.x << v3.y << v3.z << ")";

    }

    Point2D p1, p2, p3;
    p1.x = vert[0];
    p1.y = vert[1];

    p2.x = vert[2];
    p2.y = vert[3];

    p3.x = vert[4];
    p3.y = vert[5];


    for(int j = start.y(); j < render_size.height(); j++)
    {
        for(int i = start.x(); i < render_size.width(); i++)
        {
            Point2D pt;
            pt.x = i;
            pt.y = render_size.height() - j;
            if( PointInTriangle(pt, p1, p2, p3) )
                framebuffer->set(i, j, rgb(0xff000000));
            else
                framebuffer->set(i, j, rgb(0xffff0a0a));
        }
    }


    return false;
}
