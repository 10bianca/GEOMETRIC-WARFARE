#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "lab_m1/Tema1/objects2D.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/Tema1.h"

using namespace std;
using namespace m1;
using namespace std::chrono;

struct Hexagon{
	Mesh* hexagon;
	float x, y, size;
	glm::vec3 color;
	int starsFired;
	float scale;
};

std::vector<Hexagon> hexagons;

struct Diamond {
	Mesh* diamond;
	float x, y, height, width;
	glm::vec3 color;
	bool remove;
	float scale = 1.0f;
};

std::vector<Diamond> diamonds;

struct Rectangle {
	Mesh* rectangle;
	float x, y, height, width;
	glm::vec3 color;
	bool remove;
	float scale;
};

std::vector<Rectangle> rectangles;

struct Star {
	Mesh* star;
	float x, y, size;
	glm::vec3 color;
	bool remove;
};

std::vector<Star> stars;
std::vector<Star> starsOnScreen;
std::vector<Star> starsAvailable;

struct Live {
	float x, y, size;
};
std::vector<Live> lives;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void AddHexagon(int pos_x, int pos_y, glm::vec3 hexagon_color, int size, Mesh *hexagon, int starsFired, float scale){
	Hexagon hexagonn;
	hexagonn.x = pos_x; 
	hexagonn.y = pos_y;
	hexagonn.size = size;
	hexagonn.color = hexagon_color;
	hexagonn.hexagon = hexagon;
	hexagonn.starsFired = starsFired;
	hexagonn.scale = scale;

	hexagons.push_back(hexagonn);

}

void AddDiamond(int pos_x, int pos_y, glm::vec3 diamond_color, int height, int width, Mesh* diamond, bool remove, float scale) {
	Diamond diamondd;
	diamondd.x = pos_x; 
	diamondd.y = pos_y;
	diamondd.height = height;
	diamondd.width = width;
	diamondd.color = diamond_color;
	diamondd.diamond = diamond;
	diamondd.remove = remove;
	diamondd.scale = scale;
	
	diamonds.push_back(diamondd);

}

void AddRectangle(int pos_x, int pos_y, glm::vec3 rectangle_color, int height, int width, Mesh* rectangle, bool remove, float scale) {
	Rectangle rectanglee;
	rectanglee.x = pos_x; 
	rectanglee.y = pos_y;
	rectanglee.height = height;
	rectanglee.width = width;
	rectanglee.color = rectangle_color;
	rectanglee.rectangle = rectangle;
	rectanglee.remove = remove;
	rectanglee.scale = scale;

	rectangles.push_back(rectanglee);

}

void AddStar(int pos_x, int pos_y, glm::vec3 star_color, int size, Mesh* star, bool remove) {
	Star starr;
	starr.x = pos_x;
	starr.y = pos_y;
	starr.size = size;
	starr.color = star_color;
	starr.star = star;
	starr.remove = remove;

	stars.push_back(starr);

}

void AddStarOnScreen(int pos_x, int pos_y, glm::vec3 star_color, int size, Mesh* star, bool remove) {
	Star starr;
	starr.x = pos_x; 
	starr.y = pos_y;
	starr.size = size;
	starr.color = star_color;
	starr.star = star;
	starr.remove = remove;

	starsOnScreen.push_back(starr);

}

void AddStarsAvailable(int pos_x, int pos_y, glm::vec3 star_color, int size, Mesh* star, bool remove) {
	Star starr;
	starr.x = pos_x; 
	starr.y = pos_y;
	starr.size = size;
	starr.color = star_color;
	starr.star = star;
	starr.remove = remove;

	starsAvailable.push_back(starr);

}

void AddLives(int x, int y, int size)
{
	Live livess;
	livess.x = x;
	livess.y = y;
	livess.size = size;

	lives.push_back(livess);
}


void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	width = resolution.x;
	height = resolution.y;
	glm::vec3 red = glm::vec3(1.0f, 0.2f, 0.2f);


	Mesh* barrier = objects2D::CreateRectangle("barrier", glm::vec3(0, 0, 2), height/1.8, width/23, red, true);
	AddMeshToList(barrier);

	start_x_init = width/23 + 10 + 20;
	start_y_init = 10;
	start_x = start_x_init;
	start_y = start_y_init;
	square_size = ((height / 1.8) - 40) / 3;
	timeShotsFired = 1;

	for (int i = 0; i < 3; i++)
	{
		

		for (int j = 0; j < 3; j++)
		{
			std::string square_i_j = "grid[" + std::to_string(i) + "][" + std::to_string(j) + "]";
			Mesh* squares = objects2D::CreateRectangle(square_i_j, glm::vec3(0, 0, -1), square_size, square_size, green, true);
			AddMeshToList(squares);
			start_x = start_x + square_size + 20;
			
		}

		start_x = start_x_init;
		start_y = start_y + square_size + 20;
	}

	
	Mesh* diamond1 = objects2D::CreateDiamond("diamond1", glm::vec3(0, 0, 0), square_size/2, square_size/4, pink, true);
	AddMeshToList(diamond1);
	Mesh* rectangle1 = objects2D::CreateRectangle("rectangle1", glm::vec3(0, 0, 0), square_size/4, square_size/2 - 5, pink, true);
	AddMeshToList(rectangle1);
	Mesh* rectangleEmpty1 = objects2D::CreateRectangleEmpty("rectangleEmpty1", glm::vec3(0, 0, 0), square_size, square_size, white);
	AddMeshToList(rectangleEmpty1);

	Mesh* star1_1 = objects2D::CreateStar("star1_1", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star1_1);

	Mesh* diamond2 = objects2D::CreateDiamond("diamond2", glm::vec3(0, 0, 0), square_size / 2, square_size / 4, violet, true);
	AddMeshToList(diamond2);
	Mesh* rectangle2 = objects2D::CreateRectangle("rectangle2", glm::vec3(0, 0, 0), square_size / 4, square_size / 2 - 5, violet, true);
	AddMeshToList(rectangle2);
	Mesh* rectangleEmpty2 = objects2D::CreateRectangleEmpty("rectangleEmpty2", glm::vec3(0, 0, 0), square_size, square_size, white);
	AddMeshToList(rectangleEmpty2);

	Mesh* star2_1 = objects2D::CreateStar("star2_1", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star2_1);
	Mesh* star2_2 = objects2D::CreateStar("star2_2", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star2_2);


	Mesh* diamond3 = objects2D::CreateDiamond("diamond3", glm::vec3(0, 0, 0), square_size / 2, square_size / 4, blue, true);
	AddMeshToList(diamond3);
	Mesh* rectangle3 = objects2D::CreateRectangle("rectangle3", glm::vec3(0, 0, 0), square_size / 4, square_size / 2 - 5, blue, true);
	AddMeshToList(rectangle3);
	Mesh* rectangleEmpty3 = objects2D::CreateRectangleEmpty("rectangleEmpty3", glm::vec3(0, 0, 0), square_size, square_size, white);
	AddMeshToList(rectangleEmpty3);

	Mesh* star3_1 = objects2D::CreateStar("star3_1", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star3_1);
	Mesh* star3_2 = objects2D::CreateStar("star3_2", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star3_2);

	Mesh* diamond4 = objects2D::CreateDiamond("diamond4", glm::vec3(0, 0, 0), square_size / 2, square_size / 4, orange, true);
	AddMeshToList(diamond4);
	Mesh* rectangle4 = objects2D::CreateRectangle("rectangle4", glm::vec3(0, 0, 0), square_size / 4, square_size / 2 - 5, orange, true);
	AddMeshToList(rectangle4);
	Mesh* rectangleEmpty4 = objects2D::CreateRectangleEmpty("rectangleEmpty4", glm::vec3(0, 02, 0), square_size, square_size, white);
	AddMeshToList(rectangleEmpty4);

	Mesh* star4_1 = objects2D::CreateStar("star4_1", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star4_1);
	Mesh* star4_2 = objects2D::CreateStar("star4_2", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star4_2);
	Mesh* star4_3 = objects2D::CreateStar("star4_3", glm::vec3(0, 0, 0), square_size / 6, pink, true);
	AddMeshToList(star4_3);

	// LIVES
	Mesh* live1 = objects2D::CreateRectangle("live1", glm::vec3(0, 0 , 0), square_size/2, square_size/ 2, red, true);
	AddMeshToList(live1);

 
    // HEXAGOANE
	Mesh* hexagon1 = objects2D::CreateHexagon("hexagon1", glm::vec3(0, 0, 0), 50, pink, true);
	AddMeshToList(hexagon1);
	Mesh* hexagon2 = objects2D::CreateHexagon("hexagon2", glm::vec3(0, 0, 0), 50, violet, true);
	AddMeshToList(hexagon2);
	Mesh* hexagon3 = objects2D::CreateHexagon("hexagon3", glm::vec3(0, 0, 0), 50, blue, true);
	AddMeshToList(hexagon3);
	Mesh* hexagon4 = objects2D::CreateHexagon("hexagon4", glm::vec3(0, 0, 0), 50, orange, true);
	AddMeshToList(hexagon4);
	Mesh* hexagonSmall = objects2D::CreateHexagon("hexagonSmall", glm::vec3(0, 0, 1), 25, glm::vec3(0.4f, 1.0f, 0.4f), true);
	AddMeshToList(hexagonSmall);

	// STELUTE PE ECRAN
	Mesh* starOnScreen = objects2D::CreateStar("starOnScreen", glm::vec3(0, 0, 4), square_size / 6, glm::vec3 (0.5f, 0.5f, 0.5f), true);
	AddMeshToList(starOnScreen);

   // STELE FIRED
	Mesh* starFired1 = objects2D::CreateStar("starFired1", glm::vec3(0, 0, 1), square_size / 6, pink, true);
	AddMeshToList(starFired1);
	Mesh* starFired2 = objects2D::CreateStar("starFired2", glm::vec3(0, 0, 1), square_size / 6, violet, true);
	AddMeshToList(starFired2);
	Mesh* starFired3 = objects2D::CreateStar("starFired3", glm::vec3(0, 0, 1), square_size / 6, blue, true);
	AddMeshToList(starFired3);
	Mesh* starFired4 = objects2D::CreateStar("starFired4", glm::vec3(0, 0, 1), square_size / 6, orange, true);
	AddMeshToList(starFired4);

 
	translateX = 0;
	translateY = 0;
 
	nrPointStars = 5;

	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			vectorSquares[i][j] = 0;
		}
	}

	nrLives = 3;
}

 

void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

float angularStep = 0.0f;
void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	glm::mat3 barrierMatrix = transform2D::Translate(10, 10);
	RenderMesh2D(meshes["barrier"], shaders["VertexColor"], barrierMatrix);

	start_x = start_x_init;
	start_y = start_y_init;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			squareGrid = glm::mat3(1) * transform2D::Translate(start_x, start_y);
			RenderMesh2D(meshes["grid[" + std::to_string(i) + "][" + std::to_string(j) + "]"], shaders["VertexColor"], squareGrid);
			start_x = start_x + square_size + 20;
		}

		start_x = start_x_init;
		start_y = start_y + square_size + 20;
	}

	distance1 = 100;
	distance2 = distance1 + 50 + square_size;
	distance3 = distance2 + 50 + square_size;
	distance4 = distance3 + 50 + square_size;


	// TURETA 1
	glm::mat3 diamondMatrix1 = glm::mat3(1) * transform2D::Translate(distance1, height - 80);
	glm::mat3 rectangleMatrix1 = glm::mat3(1) * transform2D::Translate(distance1, height - 95);
	glm::mat3 emptyRectangleMatrix1 = glm::mat3(1) * transform2D::Translate(distance1 - square_size / 2, height - 80 - square_size / 2);


	RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], diamondMatrix1);
	RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], rectangleMatrix1);
	RenderMesh2D(meshes["rectangleEmpty1"], shaders["VertexColor"], emptyRectangleMatrix1);


	// TURETA 2
	glm::mat3 diamondMatrix2 = glm::mat3(1) * transform2D::Translate(distance2, height - 80);
	glm::mat3 rectangleMatrix2 = glm::mat3(1) * transform2D::Translate(distance2, height - 95);
	glm::mat3 emptyRectangleMatrix2 = glm::mat3(1) * transform2D::Translate(distance2 - square_size / 2, height - 80 - square_size / 2);


	RenderMesh2D(meshes["diamond2"], shaders["VertexColor"], diamondMatrix2);
	RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], rectangleMatrix2);
	RenderMesh2D(meshes["rectangleEmpty2"], shaders["VertexColor"], emptyRectangleMatrix2);


	// TURETA 3
	glm::mat3 diamondMatrix3 = glm::mat3(1) * transform2D::Translate(distance3, height - 80);
	glm::mat3 rectangleMatrix3 = glm::mat3(1) * transform2D::Translate(distance3, height - 95);
	glm::mat3 emptyRectangleMatrix3 = glm::mat3(1) * transform2D::Translate(distance3 - square_size / 2, height - 80 - square_size / 2);


	RenderMesh2D(meshes["diamond3"], shaders["VertexColor"], diamondMatrix3);
	RenderMesh2D(meshes["rectangle3"], shaders["VertexColor"], rectangleMatrix3);
	RenderMesh2D(meshes["rectangleEmpty3"], shaders["VertexColor"], emptyRectangleMatrix3);


	// TURETA 4
	glm::mat3 diamondMatrix4 = glm::mat3(1) * transform2D::Translate(distance4, height - 80);
	glm::mat3 rectangleMatrix4 = glm::mat3(1) * transform2D::Translate(distance4, height - 95);
	glm::mat3 emptyRectangleMatrix4 = glm::mat3(1) * transform2D::Translate(distance4 - square_size / 2, height - 80 - square_size / 2);



	RenderMesh2D(meshes["diamond4"], shaders["VertexColor"], diamondMatrix4);
	RenderMesh2D(meshes["rectangle4"], shaders["VertexColor"], rectangleMatrix4);
	RenderMesh2D(meshes["rectangleEmpty4"], shaders["VertexColor"], emptyRectangleMatrix4);


	// STELE
	glm::mat3 starMatrix = glm::mat3(1) * transform2D::Translate(distance1 - square_size / 3, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star1_1"], shaders["VertexColor"], starMatrix);

	starMatrix = glm::mat3(1) * transform2D::Translate(distance2 - square_size / 3, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star2_1"], shaders["VertexColor"], starMatrix);
	starMatrix = glm::mat3(1) * transform2D::Translate(distance2 - square_size / 3 + 40, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star2_2"], shaders["VertexColor"], starMatrix);

	starMatrix = glm::mat3(1) * transform2D::Translate(distance3 - square_size / 3, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star3_1"], shaders["VertexColor"], starMatrix);
	starMatrix = glm::mat3(1) * transform2D::Translate(distance3 - square_size / 3 + 40, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star3_2"], shaders["VertexColor"], starMatrix);

	starMatrix = glm::mat3(1) * transform2D::Translate(distance4 - square_size / 3, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star4_1"], shaders["VertexColor"], starMatrix);
	starMatrix = glm::mat3(1) * transform2D::Translate(distance4 - square_size / 3 + 40, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star4_2"], shaders["VertexColor"], starMatrix);
	starMatrix = glm::mat3(1) * transform2D::Translate(distance4 - square_size / 3 + 80, height - 80 - (2 * square_size / 3));
	RenderMesh2D(meshes["star4_3"], shaders["VertexColor"], starMatrix);

	// LIVES
	int distance5 = distance4 + square_size + 200; 
	glm::mat3 liveMatrix = glm::mat3(1) * transform2D::Translate(distance5, height - 40 - square_size / 2);

	for (int i = 0 ; i < nrLives ; i++)
	{
		AddLives(distance5, height - 40 - square_size / 2, square_size / 2);
		glm::mat3 liveMatrix = glm::mat3(1) * transform2D::Translate(distance5, height - 40 - square_size / 2);
		RenderMesh2D(meshes["live1"], shaders["VertexColor"], liveMatrix);
		distance5 += square_size / 2 + 25;

	}
	
	
	// STELUTE STRANSE
	int beginX = distance4 + square_size + 200 + square_size / 6;
	int beginY = height - 40 - square_size / 2 - square_size / 6;
	for (int i = 0; i < nrPointStars; i++)
	{
		AddStarsAvailable(beginX, beginY, glm::vec3(0.5f, 0.5f, 0.5f), square_size / 6, meshes["starOnScreen"], false);
		glm::mat3 starOnScreenMatrix = glm::mat3(1) * transform2D::Translate(beginX, beginY);
		RenderMesh2D(meshes["starOnScreen"], shaders["VertexColor"], starOnScreenMatrix);
		beginX += square_size / 6 + 20;
	}





	srand(static_cast<unsigned int>(time(NULL)));
	randomWaitTime = randomWaitTime - deltaTimeSeconds;
	// prima linie din matricea de patrate are y = 10
    // a doua linie y = 10 + square_size + 20 = 30 + square_size
	// a treia linie y = 50 + 2 * square_size
	// o sa mai adaug square_size / 2 la fiecare valoare, deoarece dimensiunile date sunt pentru varful din stanga jos al unui patrat
	// iar hexagonul este format in jurul unui centru care trebuie sa fie mai sus decat acel colt
	std::vector<int> hexagon_lines_y = { 10 + square_size / 2, 30 + (3 * square_size) / 2, 50 + (5 * square_size) / 2 };
	std::vector<glm::vec3> hexagon_color = {
		pink,   
		violet,  
		blue,    
		orange   
	};

	// HEXAGOANE
	if (randomWaitTime <= 0.0f && hexagons.size() <= 5) {

		// ce hexagon randam
		int randomIndex1 = rand() % 4;

		// pe ce linie randam
		int randomIndex2 = rand() % 3;
		int line = hexagon_lines_y[randomIndex2];

		// culoare și linie aleatoare
		glm::vec3 randomColor = hexagon_color[randomIndex1];

		std::string hexagon_i = "hexagon" + std::to_string(randomIndex1 + 1);

		AddHexagon(width, line, randomColor, 50, meshes[hexagon_i], 0, 1.0f);

		randomWaitTime = static_cast<float>(rand()) / RAND_MAX * 1.0f + 15.0f;

	}

 	for (auto it = hexagons.begin(); it != hexagons.end(); )
	{
		Hexagon& hexagon = *it;

		translateX = 50 * deltaTimeSeconds;

		glm::mat3 modelMatrix = glm::mat3(1) * transform2D::Translate(hexagon.x, hexagon.y);

		hexagon.x = hexagon.x - translateX;

		if (hexagon.x > 60.0f && hexagon.starsFired < 3)
		{
			RenderMesh2D(hexagon.hexagon, shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["hexagonSmall"], shaders["VertexColor"], modelMatrix);
			++it;
		}
		else if(hexagon.x <= 60.0f )
		{
			    // daca trece de bariera il stergem
				it = hexagons.erase(it);
				nrLives--;
			
		}
		else if (hexagon.starsFired >= 3)
		{
			// daca e impuscat de 3 ii facem animatia de disparitie si il stergem dupa
			hexagon.scale -= deltaTimeSeconds;
			if (hexagon.scale >= 0.0f)
			{
 				glm::mat3 dissapearHexagon = glm::mat3(1) * transform2D::Translate(hexagon.x, hexagon.y) * transform2D::Scale(hexagon.scale, hexagon.scale);
				RenderMesh2D(hexagon.hexagon, shaders["VertexColor"], dissapearHexagon);
				RenderMesh2D(meshes["hexagonSmall"], shaders["VertexColor"], dissapearHexagon);
				++it;

			}
			else it = hexagons.erase(it);
		}
	}

	glm::vec2 cursorPosition = window->GetCursorPosition();
	glm::mat3 modelMatrix3_1 = glm::mat3(1) * transform2D::Translate(cursorPosition.x, resolution.y - cursorPosition.y);
	glm::mat3 modelMatrix3_2 = glm::mat3(1) * transform2D::Translate(cursorPosition.x, resolution.y - cursorPosition.y - 15);
	if (nr_diamond == 1 && dragged) {

		RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix3_1);
		RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix3_2);
	}

	else if (nr_diamond == 2 && dragged) {

		RenderMesh2D(meshes["diamond2"], shaders["VertexColor"], modelMatrix3_1);
		RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix3_2);
	}

	else if (nr_diamond == 3 && dragged) {

		RenderMesh2D(meshes["diamond3"], shaders["VertexColor"], modelMatrix3_1);
		RenderMesh2D(meshes["rectangle3"], shaders["VertexColor"], modelMatrix3_2);
	}

	else if (nr_diamond == 4 && dragged) {

		RenderMesh2D(meshes["diamond4"], shaders["VertexColor"], modelMatrix3_1);
		RenderMesh2D(meshes["rectangle4"], shaders["VertexColor"], modelMatrix3_2);
	}

	for (auto it = diamonds.begin(); it != diamonds.end(); ++it)
	{
		Diamond& diamond1 = *it;
		if (diamond1.remove == false)
		{
			RenderMesh2D(diamond1.diamond, shaders["VertexColor"], glm::mat3(1));
			 
		}
		else
		{   diamond1.scale -= deltaTimeSeconds;
		if (diamond1.scale >= 0.0f)
		{
			glm::mat3 dissapearDiamond = glm::mat3(1) * transform2D::Translate(diamond1.x, diamond1.y) * transform2D::Scale(diamond1.scale, diamond1.scale) * transform2D::Translate(-diamond1.x, -diamond1.y);
			RenderMesh2D(diamond1.diamond, shaders["VertexColor"], dissapearDiamond);
		}
		}

	}
	

	for (auto it = rectangles.begin(); it != rectangles.end(); ++it)
	{
		
		Rectangle& rectangle1 = *it;
		if (rectangle1.remove == false)
		{
			RenderMesh2D(rectangle1.rectangle, shaders["VertexColor"], glm::mat3(1));
		}

		else
		{
			rectangle1.scale -= deltaTimeSeconds;
			if (rectangle1.scale >= 0.0f)
			{
				glm::mat3 dissapearRectangle = glm::mat3(1) * transform2D::Translate(rectangle1.x, rectangle1.y + 15) * transform2D::Scale(rectangle1.scale, rectangle1.scale) * transform2D::Translate(-rectangle1.x, -rectangle1.y - 15);
				RenderMesh2D(rectangle1.rectangle, shaders["VertexColor"], dissapearRectangle);
			}
		}
	}

	if (!diamonds.empty())
	{
		for (auto i = hexagons.begin(); i != hexagons.end(); ++i)
		{
			Hexagon& hexagon1 = *i;
			for (auto j = diamonds.begin(); j != diamonds.end(); ++j)
			{
				Diamond& diamond1 = *j;
				if (diamond1.y == hexagon1.y && diamond1.color == hexagon1.color)
				{    
					// daca nu a disparut, trage cu stelute
					if (timeShotsFired <= 0 && diamond1.remove == false)
					{
						// STELE FIRED
							if (diamond1.color == pink)
								AddStar(diamond1.x, diamond1.y, diamond1.color, square_size / 6, meshes["starFired1"], false);
							else if (diamond1.color == violet)
								AddStar(diamond1.x, diamond1.y, diamond1.color, square_size / 6, meshes["starFired2"], false);
							else if (diamond1.color == blue)
								AddStar(diamond1.x, diamond1.y, diamond1.color, square_size / 6, meshes["starFired3"], false);
							else
								AddStar(diamond1.x, diamond1.y, diamond1.color, square_size / 6, meshes["starFired4"], false);

						timeShotsFired = 4.0f;
					}
					else
					{
						timeShotsFired -= deltaTimeSeconds;
					}

				}

			}
		}
	}



	for (auto i = stars.begin(); i != stars.end();) {

		Star& star = *i;
		translateX = 50 * deltaTimeSeconds;
		angularStep += deltaTimeSeconds;
		glm::mat3 modelMatrix5 = glm::mat3(1) * transform2D::Translate(star.x, star.y) * transform2D::Rotate(angularStep);

		if (star.x < width && star.remove == false)
		{
			star.x = star.x + translateX;
			RenderMesh2D(star.star, shaders["VertexColor"], modelMatrix5);
			i++;
		}
		else
		{
			i = stars.erase(i);
		}
	}




	// ADAUGARE STELUTE PE ECRAN
	if (timeStarsOnScreen <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			int randX = rand() % resolution.x;
			int randY = rand() % resolution.y;
			AddStarOnScreen(randX, randY, pink, square_size / 6, meshes["starOnScreen"], false);
		}
		timeStarsOnScreen = 600.0f;
	}
	else
	{
		timeStarsOnScreen -= deltaTimeSeconds;
	}


	// RANDARE STELUTE PE ECRAN
	for (auto it = starsOnScreen.begin(); it != starsOnScreen.end(); ++it) {
		Star& star = *it;
		glm::mat3 modelMatrix7 = glm::mat3(1) * transform2D::Translate(star.x, star.y);
		RenderMesh2D(star.star, shaders["VertexColor"], modelMatrix7);
	}
        
    	// COLIZIUNE STELUTA HEXAGON
		for (auto i = stars.begin(); i != stars.end();++i)
		{
			Star & star = *i;
			for (auto j = hexagons.begin(); j != hexagons.end(); ++j)
			{
				Hexagon& hexagon = *j;

				if (hexagon.y == star.y)
				{
					glm::vec3 coordS(star.x, star.y, 0);
					glm::vec3 coordH(hexagon.x, hexagon.y, 0);
					float dist = glm::distance(coordS, coordH);
					if (dist <= (star.size + hexagon.size)&& hexagon.color == star.color)
					{			
                          hexagon.starsFired++;

						  star.remove = true;
						
					}
					
					
				}
				 
			}
			 
		}

		// COLIZIUNE ROMB HEXAGON
		for (auto i = diamonds.begin(); i != diamonds.end(); ++i)
		{
			Diamond& diamond = *i;
			for (auto j = hexagons.begin(); j != hexagons.end(); ++j)
			{
				Hexagon& hexagon = *j;
				
				if (diamond.y == hexagon.y)
				{
					if (float(diamond.x + square_size / 2 - 5) - hexagon.x + hexagon.size <= 1.0f 
						&& float(diamond.x + square_size / 2 - 5) - hexagon.x + hexagon.size >= 0.0f)
					{
						diamond.remove = true;
					}
				}
			}

		}

		// COLIZIUNE DREPTUNGHI HEXAGON
		for (auto i = rectangles.begin(); i != rectangles.end(); ++i)
		{
			Rectangle& rectangle = *i;
			for (auto j = hexagons.begin(); j != hexagons.end(); ++j)
			{
				Hexagon& hexagon = *j;
				if (rectangle.y + 15 == hexagon.y)
				{
					if (float(rectangle.x + square_size / 2 - 5) - hexagon.x + hexagon.size <= 1.0f
						&& float(rectangle.x + square_size / 2 - 5) - hexagon.x + hexagon.size >= 0.0f)
						rectangle.remove = true;
				}
			}


			// DACA SE STERGE O TURETA, SE ELIBEREAZA PATRATUL
			start_y = start_y_init;
			start_x = start_x_init;
			if (rectangle.remove == true)
			{
				for (int i = 1; i <= 3; i++)
				{
					for (int j = 1; j <= 3; j++)
					{
						if (start_x + square_size / 2 == rectangle.x && start_y + square_size / 2 - 15 == rectangle.y)
						{
							vectorSquares[i][j] = 0;
						}

						start_x = start_x + square_size + 20;
					}
					start_x = start_x_init;
					start_y = start_y + square_size + 20;
				}
			}

		}
		
		
}

void Tema1::FrameEnd()
{
	if (nrLives <= 0)
	{
		ClearScreen(glm::vec3 (0, 0, 0));
	}
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
	// Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
	nr_diamond = 0;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
	{
		dragged = 1;
		int cursor_x = window->GetCursorPosition().x;
		int cursor_y = window->GetCursorPosition().y;

		// CHENAR 1
	   // prima conditie: sa fie in chenar
		if (cursor_y >= 80 - square_size / 2 && cursor_y <= 80 + square_size / 2
			&& cursor_x >= distance1 - (square_size / 2) && cursor_x <= distance1 + square_size / 2)
		{
			// ROMB1
			// a doua conditie: verificam daca cursorul este in romb
			// calculam distanta de la punct la centrul rombului
			// primul romb are centrul in (distance1, height - 80, 0)
			double distX = std::abs(cursor_x - distance1);
			double distY = std::abs(cursor_y - 80); // centrul pe verticala este in punctul 80

			// height = square_size/2, width = square_size/4
			// distX / width <= 1 => punctul se afla in stanga sau in dreapta marginii rombului
			// distY / height <= 1 => punctul se  afla sub sau pe marginea superioara a rombului
			if ((distX / (square_size / 4)) + (distY / (square_size / 2)) <= 1.0)
				nr_diamond = 1;
			else {
				// DREPTUNGHI1
				// daca nu este in romb, poate fi in dreptunghi
				// height = square_size / 4, width = square_size / 2


				if (cursor_x >= distance1 && cursor_x <= distance1 +  (square_size / 2)
					&& cursor_y <= 95 && cursor_y >= 95 - (square_size / 4))
					nr_diamond = 1;

				else nr_diamond = 0;

			}
		}
		// CHENAR2
		else if (cursor_y >= 80 - square_size / 2 && cursor_y <= 80 + square_size / 2
			&& cursor_x >= distance2 - (square_size / 2) && cursor_x <= distance2 + square_size / 2)
		{
			double distX = std::abs(cursor_x - distance2);
			double distY = std::abs(cursor_y - 80); 

			if ((distX / (square_size / 4)) + (distY / (square_size / 2)) <= 1.0)
				nr_diamond = 2;
			else
			{
				// DREPTUNGHI2
				if (cursor_x >= distance2  && cursor_x <= distance2 + (square_size / 2)
					&& cursor_y <= 95 && cursor_y >= 95 - (square_size / 4))
					nr_diamond = 2;

				else nr_diamond = 0;

			}
		}

		// CHENAR3
		else if (cursor_y >= 80 - square_size / 2 && cursor_y <= 80 + square_size / 2
			&& cursor_x >= distance3 - (square_size / 2) && cursor_x <= distance3 + (square_size / 2) )
		{
			double distX = std::abs(cursor_x - distance3);
			double distY = std::abs(cursor_y - 80); 

			if ((distX / (square_size / 4)) + (distY / (square_size / 2)) <= 1.0)
				nr_diamond = 3;
			else {
				// DREPTUNGHI2
				if (cursor_x >= distance3 && cursor_x <= distance3 + (square_size / 2)
					&& cursor_y <= 95 && cursor_y >= 95 - (square_size / 4))
					nr_diamond = 3;

				else nr_diamond = 0;

			}
		}

		else if (cursor_y >= 80 - square_size / 2 && cursor_y <= 80 + square_size / 2
			&& cursor_x >= distance4 - (square_size / 2) && cursor_x <= distance4 + (square_size / 2))
		{
			double distX = std::abs(cursor_x - distance4);
			double distY = std::abs(cursor_y - 80); 

			if ((distX / (square_size / 4)) + (distY / (square_size / 2)) <= 1.0)
				nr_diamond = 4;
			else 
			{
				// DREPTUNGHI2
				if (cursor_x >= distance4 && cursor_x <= distance4 + (square_size / 2)
					&& cursor_y <= 95 && cursor_y >= 95 - (square_size / 4))
					nr_diamond = 4;

				else nr_diamond = 0;

			}
		}
		else nr_diamond = 0;

		
	
	
	
	int beginY = height - 40 - square_size / 2 - square_size / 6;
	for (auto it = starsOnScreen.begin(); it != starsOnScreen.end();)
	{
		int starX = (*it).x;
		int starY = (*it).y;

		if (mouseX >= starX - square_size / 6 && mouseX <= starX + square_size / 6 &&
			mouseY <= height - starY + square_size / 6 && mouseY >= height - starY - square_size / 6) 
		{
			nrPointStars++;
			it = starsOnScreen.erase(it); 
		}
		else
		{
			++it;
		}
	}
	 
    } 
	
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		for (auto i = diamonds.begin(); i != diamonds.end(); ++i)
		{
			int diamondX = (*i).x;
			int diamondY = (*i).y;

			for (auto j = rectangles.begin(); j != rectangles.end(); ++j)
			{
				int rectangleX = (*j).x;
				int rectangleY = (*j).y;

				// DACA APAS PE ROMB
				if (mouseX >= diamondX - square_size / 4 && mouseX <= diamondX + square_size / 4
					&& mouseY <= height - diamondY + square_size / 2 && mouseY >= height - diamondY - square_size / 2)
				{
					(*i).remove = true;
				}

				// DACA APAS PE DREPTUNGHI  
				if (mouseX >= rectangleX && mouseX <= rectangleX + square_size / 2
					&& mouseY <= height - rectangleY && mouseY >= height - rectangleY - square_size / 2)
				{
					(*j).remove = true;
				}
			}
		}

	}

		
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	nr_square = 0;
	int current_square = 0;

	// daca cursorul este pe un patrat
    start_y = start_y_init;
	start_x = start_x_init;

	// daca se afla in cadrul matricei de patrate
			
	for (int i = 1; i <= 3; i++)
	{
	   for (int j = 1; j <= 3; j++)
	   {
		current_square++;
           if (mouseY <= height - start_y && mouseY >= height - start_y - square_size)
	       {
	           // daca patratul nu este ocupat
	           // si cursorul este in patrat
 			   if (vectorSquares[i][j] != current_square &&
				   mouseX >= start_x && mouseX <= start_x + square_size)
			   {
				   nr_square = current_square;
				   dragged = 0;
				   // daca am stelute disponibile
				   if (nr_diamond == 1 && nrPointStars >= 1)
				   {
					   Diamond diamond;
					   Mesh* diamondSquare1 = objects2D::CreateDiamond("diamondSquare1", glm::vec3(start_x + square_size / 2, start_y + square_size / 2, 0), square_size / 2, square_size / 4, pink, true);
					   AddMeshToList(diamondSquare1);
					   AddDiamond(start_x + square_size / 2, start_y + square_size / 2, pink, square_size / 2, square_size / 4, diamondSquare1, false, 1.0f);

					   Rectangle rectangle;
					   Mesh* rectangleSquare1 = objects2D::CreateRectangle("rectangleSquare1", glm::vec3(start_x + square_size / 2, start_y + square_size / 2 - 15, 0), square_size / 4, square_size / 2 - 5, pink, true);
					   AddMeshToList(rectangleSquare1);
					   AddRectangle(start_x + square_size / 2, start_y + square_size / 2 - 15, pink, square_size / 4, square_size / 2, rectangleSquare1, false, 1.0f);
					   nrPointStars--;
				   }

				   if (nr_diamond == 2 && nrPointStars >= 2)
				   {
					   Diamond diamond;
					   Mesh* diamondSquare2 = objects2D::CreateDiamond("diamondSquare2", glm::vec3(start_x + square_size / 2, start_y + square_size / 2, 0), square_size / 2, square_size / 4, violet, true);
					   AddMeshToList(diamondSquare2);
					   AddDiamond(start_x + square_size / 2, start_y + square_size / 2 , violet, square_size / 2, square_size / 4, diamondSquare2, false, 1.0f);

					   Rectangle rectangle;
					   Mesh* rectangleSquare2 = objects2D::CreateRectangle("rectangleSquare2", glm::vec3(start_x + square_size / 2, start_y + square_size / 2 - 15, 0), square_size / 4, square_size / 2 - 5, violet, true);
					   AddMeshToList(rectangleSquare2);
					   AddRectangle(start_x + square_size / 2, start_y + square_size / 2 - 15, violet, square_size / 4, square_size / 2, rectangleSquare2, false, 1.0f);
					   nrPointStars -= 2;
				   }

				   if (nr_diamond == 3 && nrPointStars >= 2)
				   {
					   Diamond diamond;
					   Mesh* diamondSquare3 = objects2D::CreateDiamond("diamondSquare3", glm::vec3(start_x + square_size / 2, start_y + square_size / 2, 0), square_size / 2, square_size / 4, blue, true);
					   AddMeshToList(diamondSquare3);
					   AddDiamond(start_x + square_size / 2, start_y + square_size / 2, blue, square_size / 2, square_size / 4, diamondSquare3, false, 1.0f);

					   Rectangle rectangle;
					   Mesh* rectangleSquare3 = objects2D::CreateRectangle("rectangleSquare3", glm::vec3(start_x + square_size / 2, start_y + square_size / 2 - 15, 0), square_size / 4, square_size / 2 - 5, blue, true);
					   AddMeshToList(rectangleSquare3);
					   AddRectangle(start_x + square_size / 2, start_y + square_size / 2 - 15, blue, square_size / 4, square_size / 2, rectangleSquare3, false, 1.0f);
					   nrPointStars -= 2;
				   }

				   if (nr_diamond == 4 && nrPointStars >= 3)
				   {
					   Diamond diamond;
					   Mesh* diamondSquare4 = objects2D::CreateDiamond("diamondSquare4", glm::vec3(start_x + square_size / 2, start_y + square_size / 2, 0), square_size / 2, square_size / 4, orange, true);
					   AddMeshToList(diamondSquare4);
					   AddDiamond(start_x + square_size / 2, start_y + square_size / 2, orange, square_size / 2, square_size / 4, diamondSquare4, false, 1.0f);

					   Rectangle rectangle;
					   Mesh* rectangleSquare4 = objects2D::CreateRectangle("rectangleSquare4", glm::vec3(start_x + square_size / 2, start_y + square_size / 2 - 15, 0), square_size / 4, square_size / 2 - 5, orange, true);
					   AddMeshToList(rectangleSquare4);
					   AddRectangle(start_x + square_size / 2, start_y + square_size / 2 - 15, orange, square_size / 4, square_size / 2, rectangleSquare4, false, 1.0f);
					   nrPointStars -= 3;
				   }
				   // ocup patratul
				   vectorSquares[i][j] = current_square;
			   }
			   
	       }
         start_x = start_x + square_size + 20;
						
	   }
	 
	start_x = start_x_init;
	start_y = start_y + square_size + 20;
	}

	if (nr_square == 0)
		nr_diamond = 0;



}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}