#include "Animal.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include <iostream>
using namespace std;

// Abdelaziz Feature 7 start
Product::Product(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void Product::draw() const
{
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

Egg::Egg(Game* r_pGame, point r_point, int r_width, int r_height)
	: Product(r_pGame, r_point, r_width, r_height, "images\\egg.jpg")
{
}
// Abdelaziz Feature 7 end

Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	curr_pos = r_point;
	curr_vel.x = (rand() % 2 == 0) ? 1 : -1;
	curr_vel.y = (rand() % 2 == 0) ? 1 : -1;

	// Abdelaziz Feature 19 start
	lastDropTime = time(0);
	// Abdelaziz Feature 19 end
}

// Abdelaziz Feature 4 start
// Abdelaziz Feature 21 start
void Animal::draw() const
{
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);

	int interval = getProductionInterval();
	if (interval > 0)
	{
		int elapsed = (int)(time(0) - lastDropTime);
		if (elapsed > interval) elapsed = interval;

		string counterText = to_string(elapsed) + "/" + to_string(interval);
		int textX = RefPoint.x + 5;
		int textY = RefPoint.y - 22;

		pWind->SetPen(BLACK, 1);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(textX - 4, textY - 2, textX + 58, textY + 18);
		pWind->SetPen(BLACK, 1);
		pWind->SetFont(14, BOLD, BY_NAME, "Arial");
		pWind->DrawString(textX, textY, counterText);
	}
}
// Abdelaziz Feature 21 end
// Abdelaziz Feature 4 end

Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Animal(r_pGame, r_point, r_width, r_height, img_path)
{
}

// Abdelaziz Feature 4 start
void Chick::moveStep()
{
	curr_pos.x += curr_vel.x;
	curr_pos.y += curr_vel.y;

	if (curr_pos.x < config.range_min_x || curr_pos.x > config.range_max_x - width)
		curr_vel.x *= -1;

	if (curr_pos.y < config.range_min_y || curr_pos.y > config.range_max_y - height)
		curr_vel.y *= -1;

	RefPoint = curr_pos;
}
// Abdelaziz Feature 4 end

// Abdelaziz Feature 7 start
// Abdelaziz Feature 19 start
void Chick::produce(time_t currentTime)
{
	if (currentTime - lastDropTime >= getProductionInterval())
	{
		lastDropTime = currentTime;
		point dropPos = { RefPoint.x, RefPoint.y + height + 5 };
		pGame->addProduct(new Egg(pGame, dropPos, 40, 40));
	}
}
// Abdelaziz Feature 19 end
// Abdelaziz Feature 7 end

Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Animal(r_pGame, r_point, r_width, r_height, img_path)
{
}

void Cow::moveStep()
{
	curr_pos.x += curr_vel.x;
	curr_pos.y += curr_vel.y;

	if (curr_pos.x < config.range_min_x || curr_pos.x > config.range_max_x - width)
		curr_vel.x *= -1;

	if (curr_pos.y < config.range_min_y || curr_pos.y > config.range_max_y - height)
		curr_vel.y *= -1;

	RefPoint = curr_pos;
}
