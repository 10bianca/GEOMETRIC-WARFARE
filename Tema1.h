#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
 
        GLboolean moveRight;
        GLfloat posSunX, posSunY;
        float width, height;
        int square_size;
        int distance1, distance2, distance3, distance4;
        int LINE1, LINE2, LINE3, LINE4;
        glm::vec3 COLOR1, COLOR2, COLOR3, COLOR4;
        float randomWaitTime = 10.0f;
        int dragged = 0;
        int nr_diamond;
        int nr_square;
        int vectorSquares[3][3];
        float translateX1;
        glm::mat3 squareGrid;
        int start_x_init;
        int start_y_init;
        int start_x;
        int start_y;
        int shotsFired = 0;
        float timeShotsFired = 0;
        int timeStarsOnScreen = 0;
        int nrPointStars ;
        int nrLives;
        int timeDissapear = 4.0f;

        // colors
        glm::vec3 green = glm::vec3(0.4f, 1.0f, 0.4f);
        glm::vec3 white = glm::vec3(1, 1, 1);
        glm::vec3 pink = glm::vec3(1.0f, 0.4f, 0.6980f);
        glm::vec3 violet = glm::vec3(0.6f, 0.2f, 1.0f);
        glm::vec3 blue = glm::vec3(0.4f, 0.6980f, 1.0f);
        glm::vec3 orange = glm::vec3(1.0f, 0.6f, 0.2f);
     
    };
}   // namespace m1
