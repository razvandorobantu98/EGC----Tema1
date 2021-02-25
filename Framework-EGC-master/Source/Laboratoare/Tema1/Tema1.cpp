//Dorobantu Razvan-Florin, 335CB

#include "Tema1.h"
#include <vector>
#include <iostream>
#include <string>
#include <Core/Engine.h>
#include "Transformari2D.h"
#include "Obiecte2D.h"
using namespace std;

Tema1::Tema1() {

}

Tema1::~Tema1() {

}

void Tema1::Init() {

	//seteaza camera
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	//construieste meshurile pasare
	Mesh* head = Obiecte2D::CreateCircle("head", glm::vec3(0.95, 0.75, 0));
	AddMeshToList(head);

	Mesh* body = Obiecte2D::CreateCircle("body", glm::vec3(0.95, 0.75, 0));
	AddMeshToList(body);

	Mesh* eye = Obiecte2D::CreateCircle("eye", glm::vec3(0, 0, 0));
	AddMeshToList(eye);

	Mesh* beak = Obiecte2D::CreateTriangle("beak", glm::vec3(1, 0, 0));
	AddMeshToList(beak);

	Mesh* tail = Obiecte2D::CreateTriangle("tail", glm::vec3(0.95, 0.75, 0));
	AddMeshToList(tail);

	//construieste meshurile obstacole
	string meshNames[] = { "pipeGreen", "pipeBlue", "pipeRed", "pipeYellow", "pipePurple" };
	glm::vec3 meshColors[] = { glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 0, 1) };

	for (int i = 0; i < 5; i++) {
		Mesh* mesh = Obiecte2D::CreateSquare(meshNames[i], meshColors[i]);
		AddMeshToList(mesh);
	}

	string meshNames2[] = { "pipeGreen2", "pipeBlue2", "pipeRed2", "pipeYellow2", "pipePurple2" };
	glm::vec3 meshColors2[] = { glm::vec3(0, 0.5, 0), glm::vec3(0, 0, 0.5), glm::vec3(0.5, 0, 0), glm::vec3(1, 0.5, 0), glm::vec3(0.5, 0, 0.5) };
	
	for (int i = 0; i < 5; i++) {
		Mesh* mesh = Obiecte2D::CreateSquare(meshNames2[i], meshColors2[i]);
		AddMeshToList(mesh);
	}

	//seteaza valorile initiale
	windowHeight = 720;
	windowWidth = 1280;
	birdInitialX = windowWidth / 5;
	birdInitialY = windowHeight / 2;
	sectionWidth = 320;

	firstStart = true;
	scoreMax = 0;
	printf("Press SPACE to start the game!\n");
}

void Tema1::startGame() {
	
	//toate variabilele sut setate la valorile initiale
	speed = 0;
	position = 0;
	listSections = { 0, 0, 0, 0, 0 };
	listColors = { 0, 0, 0, 0, 0 };
	listMoving = { 0, 0, 0, 0, 0 };
	levelPosition = 200;
	pipeDirection = true;

	gameSpeed = 0;
	score = 0;
	passed = false;

	//porneste jocul
	gameRunning = true;
	printf("Start Game!\n\n");
}

void Tema1::endGame() {
	
	//se opreste jocul si se afiseaza scorul
	gameRunning = false;

	if(scoreMax < score)
		scoreMax = score;
	printf("Game Over!\n");
	printf("Your score is: %d. Best score: %d.\n", score, scoreMax);
	printf("Press Space to try again.\n\n");
}

void Tema1::FrameStart() {

	glClearColor(0.4, 0.7, 1, 0.5);		//seteaza culoarea
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {

	glm::ivec2 resolution = window->GetResolution();

	//creeaza matricea de rotatie
	rotationMatrix = glm::mat3(1);
	if (speed > 0) {
		rotationMatrix *= Transformari2D::Translate(birdInitialX - 20, birdInitialY) * Transformari2D::Rotate(0.5) * Transformari2D::Translate(-birdInitialX + 20, -birdInitialY);
	}
	else if (speed < 0) {
		rotationMatrix *= Transformari2D::Translate(birdInitialX - 20, birdInitialY) * Transformari2D::Rotate(-0.5) * Transformari2D::Translate(-birdInitialX + 20, -birdInitialY);
	}

	//transformari ochi
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformari2D::Translate(0, position);
	modelMatrix *= rotationMatrix;
	modelMatrix *= Transformari2D::Translate(birdInitialX - 5, birdInitialY);
	modelMatrix *= Transformari2D::Scale(3, 3);
	RenderMesh2D(meshes["eye"], shaders["VertexColor"], modelMatrix);

	//transformari cap
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformari2D::Translate(0, position);
	modelMatrix *= rotationMatrix;
	modelMatrix *= Transformari2D::Translate(birdInitialX - 10, birdInitialY);
	modelMatrix *= Transformari2D::Scale(15, 15);
	RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

	//transformari corp
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformari2D::Translate(0, position);
	modelMatrix *= rotationMatrix;
	modelMatrix *= Transformari2D::Translate(birdInitialX - 30, birdInitialY);
	modelMatrix *= Transformari2D::Scale(20, 20);
	RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

	//transformari cioc
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformari2D::Translate(0, position);
	modelMatrix *= rotationMatrix;
	modelMatrix *= Transformari2D::Translate(birdInitialX, birdInitialY);
	modelMatrix *= Transformari2D::Scale(20, 20);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	//transformari coada
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformari2D::Translate(0, position);
	modelMatrix *= rotationMatrix;
	modelMatrix *= Transformari2D::Translate(birdInitialX - 60, birdInitialY);
	modelMatrix *= Transformari2D::Scale(20, 20);
	RenderMesh2D(meshes["tail"], shaders["VertexColor"], modelMatrix);

	if (gameRunning == true) {

		//modifica factorul de translatie
		position += speed * deltaTimeSeconds;

		//daca ajung in marginea de sus a ecranului, nu mai sar
		if (position > windowHeight - birdInitialY - 20) {
			position = windowHeight - birdInitialY - 20;
		}
		//daca am cazut sub marginea de jos a ecranului, jocul se termina
		else if (position < -birdInitialY + 15) {
			endGame();
		}

		//scade viteza
		speed -= 850 * deltaTimeSeconds;

		//modifica pozitia obstacolelor
		levelPosition -= (300 + gameSpeed) * deltaTimeSeconds;

		//daca primul obstacol din stanga a iesit din ecran
		if (levelPosition + 75 < 0) {

			//creeaza un nou obstacol cu o noua dimensiue
			levelPosition += sectionWidth;
			listSections.pop_front();
			int i = rand() % ((int)(windowHeight / 2));
			listSections.push_back(i);

			//creeaza culoarea obstacolului
			listColors.pop_front();
			i = rand() % 5;
			listColors.push_back(i);

			//creeaza obstacol glisant
			listMoving.pop_front();
			i = rand() % 2;
			listMoving.push_back(i);

			//creste scorul
			passed = false;
		}

		//calculeaza factorul de translatie pentru obstacolele glisante
		if(pipeDirection == true) {
			if (deltaYpipe < -25)
				pipeDirection = false;
			else
				deltaYpipe -= 50 * deltaTimeSeconds;
		}
		else {
			if (deltaYpipe > 25)
				pipeDirection = true;
			else
				deltaYpipe += 50 * deltaTimeSeconds;
		}

	}

	//copiaza listele in vectori pentru a accesa mai usor elementele
	std::copy(listSections.begin(), listSections.end(), dimensions);
	std::copy(listColors.begin(), listColors.end(), colors);
	std::copy(listMoving.begin(), listMoving.end(), moving);

	//transformari obstacole
	for (int i = 0; i < listSections.size(); i++) {

		//daca exista obstacol (inaltimea diferita de 0)
		if (dimensions[i] != 0) {

			//alege culoarea obstacolului
			numePipe = "pipe";
			if (colors[i] == 0)
				numePipe.append("Green");
			else if (colors[i] == 1)
				numePipe.append("Blue");
			else if (colors[i] == 2)
				numePipe.append("Red");
			else if (colors[i] == 3)
				numePipe.append("Yellow");
			else if (colors[i] == 4)
				numePipe.append("Purple");

			numePipe2 = numePipe;
			numePipe2.append("2");
			
			//daca obstacolul e glisant, retine factorul de translatie
			delta = 0;
			if(moving[i] == 1)
				delta = deltaYpipe;

			//creeaza marginea obstacolului de sus (capacul)
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformari2D::Translate(levelPosition + sectionWidth * i - 5, windowHeight - dimensions[i] + 15 + delta);
			modelMatrix *= Transformari2D::Scale(85, -15);
			RenderMesh2D(meshes[numePipe2], shaders["VertexColor"], modelMatrix);

			//creeaza obstacolul de sus
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformari2D::Translate(levelPosition + sectionWidth * i, windowHeight);
			modelMatrix *= Transformari2D::Scale(75, -dimensions[i] + delta);
			RenderMesh2D(meshes[numePipe], shaders["VertexColor"], modelMatrix);

			//creeaza marginea obstacolului de jos (capacul)
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformari2D::Translate(levelPosition + sectionWidth * i - 5, windowHeight / 2 - dimensions[i] + 15 - delta);
			modelMatrix *= Transformari2D::Scale(85, -15);
			RenderMesh2D(meshes[numePipe2], shaders["VertexColor"], modelMatrix);

			//creeaza obstacolul de jos cu complementul dimensiunii
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transformari2D::Translate(levelPosition + sectionWidth * i, 0);
			modelMatrix *= Transformari2D::Scale(75, windowHeight / 2 - dimensions[i] - delta);
			RenderMesh2D(meshes[numePipe], shaders["VertexColor"], modelMatrix);
		}
	}

	if (gameRunning == true) {

		//detecteaza coliziunea (daca primul obstacol are dimensiunea diferita de 0)
		if(dimensions[0] != 0) {

			//verifica daca obstacolul e glisant si retine factorl de translatie
			delta = 0;
			if (moving[0] == 1)
				delta = deltaYpipe;

			//verifica daca obstacolul a ajuns in dreptul pasarii (pe aza OY)
			if (levelPosition < birdInitialX && levelPosition + 75 > birdInitialX - 60) {

				//daca pasarea se loveste de obstacolul de sus, jocul se termina
				if (birdInitialY + position > windowHeight - dimensions[0] - 20 + delta)
					endGame();
				//daca pasarea se loveste de obstacolul de jos, jocul se termina
				else if (birdInitialY + position < windowHeight / 2 - dimensions[0] + 20 - delta)
					endGame();
			}
		}

		//daca pasarea trece de un obstacol, creste scorul si viteza jocului
		if(passed == false && levelPosition  + 75 < birdInitialX - 60 && dimensions[0] != 0) {
			score++;
			passed = true;		//retine ca am crescut deja scorul
			printf("Score: %d\n", score);

			gameSpeed = 5 * score;
			if (gameSpeed > 150)
				gameSpeed == 150;		//viteza creste pana la o limita
		}
	}
	
}

void Tema1::FrameEnd() {

}

void Tema1::OnInputUpdate(float deltaTime, int mods) {

}

void Tema1::OnKeyRelease(int key, int mods) {

}

void Tema1::OnKeyPress(int key, int mods) {
	
	if (key == GLFW_KEY_SPACE) {

		//daca abia am deschis jocul, acesta incepe la apasarea tastei space
		if (firstStart == true) {
			startGame();
			firstStart = false;
		}
		//daca jocul ruleaza deja, pasarea sare
		else if (gameRunning == true) {
			speed = 350;
		}
		//daca jocul s-a terminat, incepe din nou la apasarea tastei space
		else {
			startGame();
		}
	}
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void Tema1::OnWindowResize(int width, int height) {
}
