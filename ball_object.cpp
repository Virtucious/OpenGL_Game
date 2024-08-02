#include "ball_object.h"

BallObject::BallObject()
	: GameObject(), Radius(12.5f), Struck(true) {};

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), Radius(radius), Struck(true) {};

glm::vec2 BallObject::Move(float dt, unsigned int window_width)
{
	//if not stuck to player board
	if (!this->Struck)
	{
		//move the ball
		this->Position += this->Velocity * dt;
		//then check if outside window bounds and if so, reverse velocity and restore at correct position
		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0;
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}

		return this->Position;
	}
}

//resets the ball to initial struck position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Struck = true;
}