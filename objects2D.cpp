#include "objects2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* objects2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float height, 
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                           0, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(1);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* objects2D::CreateRectangleEmpty(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float height,
    float width,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 1, 2, 2, 3, 3, 0 };

    rectangle->SetDrawMode(GL_LINES);

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* objects2D::CreateDiamond(
    const std::string& name,
    glm::vec3 center,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    // Calculate the four vertices of the diamond
    glm::vec3 top = center + glm::vec3(0.0f, height, 0.0f);
    glm::vec3 right = center + glm::vec3(width, 0.0f, 0.0f);
    glm::vec3 bottom = center + glm::vec3(0.0f, -height, 0.0f);
    glm::vec3 left = center + glm::vec3(-width, 0.0f, 0.0f); 

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color), // A 0
        VertexFormat(top, color), //
        VertexFormat(left, color),
        VertexFormat(bottom, color),
        VertexFormat(right, color)
        
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,  // abc
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 1};

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 4 triangles. Add the remaining indices.
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);
    }
  
    diamond->InitFromData(vertices, indices);
    return diamond;
}
Mesh* objects2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float size, // raza
    glm::vec3 color,
    bool fill)
{
    float nr_1 = size / 50;
    std::vector<VertexFormat> vertices;

    vertices.push_back(VertexFormat(center, color)); // A - 0
    vertices.push_back(VertexFormat(center + glm::vec3(size, 0, 0), color)); // B - 1
    vertices.push_back(VertexFormat(center + glm::vec3(20 * nr_1, 45 * nr_1, 0), color)); // C - 2
    vertices.push_back(VertexFormat(center + glm::vec3(- 20 * nr_1, 45 * nr_1, 0), color)); // D - 3
    vertices.push_back(VertexFormat(center + glm::vec3(-size, 0, 0), color)); // E - 4
    vertices.push_back(VertexFormat(center + glm::vec3(- 20 * nr_1, -45 * nr_1, 0), color)); // F - 5
    vertices.push_back(VertexFormat(center + glm::vec3(20 * nr_1, -45 * nr_1, 0), color)); // G - 6
     

    Mesh* hexagon = new Mesh(name);

    std::vector<unsigned int> indices = { 0, 1, 2, 
                                          0, 2, 3, 
                                          0, 3, 4, 
                                          0, 4, 5, 
                                          0, 5, 6,
                                          0, 6, 1};

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Desenează hexagonul ca și triunghiuri
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(4);
        indices.push_back(5);
        
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* objects2D::CreateStar(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices;

    // size = raza
    float nr_1 = size / 20;
    

    // varf stea
    vertices.push_back(VertexFormat(center + glm::vec3(0, size, 0), color)); //A - 0
    vertices.push_back(VertexFormat(center + glm::vec3(- 4 * nr_1, 0, 0), color));//B - 1
    vertices.push_back(VertexFormat(center + glm::vec3(4 * nr_1, 0, 0), color));//C - 2


    // lateral dreapta stea
    // CONTINUI CU C - 2
    vertices.push_back(VertexFormat(center + glm::vec3( size, 0, 0), color)); //D - 3
    vertices.push_back(VertexFormat(center + glm::vec3( 0, - 8 * nr_1, 0), color)); //E - 4

    // dreapta jos
    //  IAR C - 2
    vertices.push_back(VertexFormat(center + glm::vec3(11 * nr_1, - 16 * nr_1, 0), color));//F - 5
    //  IAR E - 4

    // stanga jos
    // IAR B - 1
    vertices.push_back(VertexFormat(center + glm::vec3(- 11 * nr_1, - 16 * nr_1, 0), color)); //G - 6
    // IAR E - 4

    // lateral stanga
    // IAR B - 1
    vertices.push_back(VertexFormat(center + glm::vec3(-size, 0, 0), color)); //H - 7
   //  IAR E - 4




    Mesh* star = new Mesh(name);

    // Indici pentru a desena steaua
    std::vector<unsigned int> indices = { 0, 1, 2,
                                         2, 3, 4,
                                        2, 4, 5,
                                        1, 6, 4,
                                        1, 7, 4,
                                        1, 2, 4 // PT UMPLERE STELUTA
                                      };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(1); 
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(4);
    }

    star->InitFromData(vertices, indices);
    return star;
}
