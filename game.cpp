#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

SpriteRenderer* Renderer;
GameObject* Player;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;

}

void Game::Init()
{
	//Load shaders
	ResourceManager::LoadShader("sprite.vert", "sprite.frag", nullptr, "sprite");
	//configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
	//set render-specific controls
	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);
	//load textures
	ResourceManager::LoadTexture("resources/background.jpg", false, "background");
	ResourceManager::LoadTexture("resources/block.png", false, "block");
	ResourceManager::LoadTexture("resources/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("resources/paddle.png", true, "paddle");
	
	//load levels
	GameLevel one; one.Load("one.lvl", this->Width, this->Height/2);
	GameLevel two; two.Load("two.lvl", this->Width, this->Height/2);
	GameLevel three; three.Load("three.lvl", this->Width, this->Height/2);
	GameLevel four; four.Load("four.lvl", this->Width, this->Height/2);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	//configure game objects 
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		//move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
	}
}

void Game::Render()
{
	//draw level
	this->Levels[this->Level].Draw(*Renderer);
	//draw player
	Player->Draw(*Renderer);
}