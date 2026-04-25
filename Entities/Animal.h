#pragma once
#include "../Core/Drawable.h"
#include <ctime>

// Abdelaziz Feature 7 start
class Product : public Drawable
{
protected:
	string image_path;
public:
	Product(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
};

class Egg : public Product
{
public:
	Egg(Game* r_pGame, point r_point, int r_width, int r_height);
};
// Abdelaziz Feature 7 end

class Animal : public Drawable
{
protected:
	string image_path;

	// Abdelaziz Feature 19 start
	virtual int getProductionInterval() const { return 0; }
	// Abdelaziz Feature 19 end

public:
	point curr_pos;
	point curr_vel;

	// Abdelaziz Feature 19 start
	time_t lastDropTime;
	// Abdelaziz Feature 19 end

	Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);

	// Abdelaziz Feature 4,21 start

	virtual void draw() const override;
	// Abdelaziz Feature 4,21 end
	

	virtual void moveStep() = 0;

	// Abdelaziz Feature 19 start
	virtual void produce(time_t currentTime) = 0;
	// Abdelaziz Feature 19 end
};

class Chick : public Animal
{
public:
	Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);

	// Abdelaziz Feature 4 start
	virtual void moveStep() override;
	// Abdelaziz Feature 4 end

	// Abdelaziz Feature 7,19 start
	virtual void produce(time_t currentTime) override;
	virtual int getProductionInterval() const override { return 10; }
	// Abdelaziz Feature 7,19 end
	
};

class Cow : public Animal
{
public:
	Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void moveStep();
	virtual void produce(time_t currentTime) {}
};
