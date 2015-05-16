#include "Enemies.h" // heade file
//enables different enemies image
Enemies::Enemies(float x, float y, ALLEGRO_BITMAP *image, void(*TakeLife)(void))
{
	GameObject::Init(x, y, 5, 0, -1, 0, 35, 35);

	SetID(ENEMY);

	maxFrame = 143;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 96;
	frameHeight = 96;
	animationColumns = 21;

	if (rand() % 2)
		animationDirection = 1;
	else
		animationDirection = -1;

	Enemies::image = image;

	Enemies::TakeLife = TakeLife;
	//Enemies::TakeLife = &TakeLife;
}

void Enemies::Destroy()
{
	GameObject::Destroy();
}

void Enemies::Update()
{
	GameObject::Update();

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
			curFrame = 0;
		else if (curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}

	if (x + frameWidth < 0)
		Collided(BORDER);
}

void Enemies::Render()
{
	GameObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Enemies::Collided(int objectID)
{
	if (objectID == BORDER)
	{
		TakeLife();
	}

	if (objectID != ENEMY)
		SetAlive(false);

}