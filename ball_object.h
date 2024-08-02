#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

//Ball object holds the state of ball object inheriting 
//relevant state data from GameObject. Contains some extra
//functionality specific to Breakout's ball object that
//were too specific for within GameObject alone
class BallObject : public GameObject
{
public:
	//ball state
	float Radius;
	bool Struck;
	//constructor(s)
	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
	//moves the ball, keeping it constrained within the window bounds(except the bottom edge), returns new position
	glm::vec2 Move(float dt, unsigned int window_width);
	//resets the ball to original state with given position and velocity
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif