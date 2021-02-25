//Dorobantu Razvan-Florin, 335CB

#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
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

	void startGame();
	void endGame();

	//dimensiunile ferestrei
	float windowHeight;
	float windowWidth;

	//coordonatele initiale ale pasarii
	float birdInitialX;
	float birdInitialY;

	float speed;		//viteza pasarii pe OY
	float position;		//factor translatie pasare pe OY
	
	float levelPosition;	//pozitia primului obstacol
	float sectionWidth;		//distanta dintre obstacole
	std::list<int> listSections;	//dimensiunile obstacolelor

	std::list<int> listMoving;		//retine daca obstacolele sunt glisante sau nu
	bool pipeDirection;		//retine in ce directie se misca obstacolele glisante (sus / jos)
	float deltaYpipe;		//factorul de translatie pentru obstacolele glisante

	std::list<char> listColors;		//culoarea obstacolelor

	bool gameRunning;	//true = jocul ruleaza, false = jocul s-a terminat
	bool firstStart;	//true = am deschis jocul pentru prima data, false = am dat restart la joc

	int score;		//retine scorul
	int scoreMax;	//retine scorul maxim

	bool passed;		//retine daca pasarea a trecut de primul obstacol
	float gameSpeed;	//viteza jocului

	//vectori auxiliari in care copiez dimensiunea obstacolelor, culoarea si daca sunt glisante
	int dimensions[5];
	int colors[5];
	int moving[5];

	int delta;		//variabila auxiliara in care retin factorul de translatie al obstacolelor glisante
	
	//variabile auxiliare in care retin culoarea obstacolelor
	std::string numePipe;
	std::string numePipe2;

protected:
	glm::mat3 modelMatrix;
	glm::mat3 rotationMatrix;
};
#pragma once
