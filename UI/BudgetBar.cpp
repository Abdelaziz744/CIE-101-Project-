#include "Budgetbar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include <iostream>
using namespace std;

BudgetbarIcon::BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void BudgetbarIcon::draw() const
{
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

ChickIcon::ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}

void ChickIcon::onClick()
{
	if (pGame->budget >= 100)
	{
		pGame->budget = pGame->budget - 100;

		point p;

		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
		p.x = dist1(gen1);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dist2(range_min_y, range_max_y);
		p.y = dist2(gen2);

		// Abdelaziz Feature 4 start
		// Abdelaziz Feature 19 start
		// Abdelaziz Feature 21 start
		pGame->addAnimal(new Chick(pGame, p, 50, 50, image_path));
		// Abdelaziz Feature 21 end
		// Abdelaziz Feature 19 end
		// Abdelaziz Feature 4 end
	}
}

CowIcon::CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
}

void CowIcon::onClick()
{
	if (pGame->budget >= 200)
	{
		pGame->budget = pGame->budget - 200;

		point p;

		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> dist1(range_min_x, range_max_x);
		p.x = dist1(gen1);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dist2(range_min_y, range_max_y);
		p.y = dist2(gen2);

		pGame->addAnimal(new Cow(pGame, p, 80, 80, image_path));
	}
}
WaterIcon::WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
	foodList = new FoodArea * [20];
	for (int i = 0; i < 20; i++)
		foodList[i] = nullptr;
}

void WaterIcon::onClick()
{
	cout << "Water Icon Clicked" << endl;

	if (pGame->budget >= 20)
	{
		pGame->budget -= 20;
		pGame->clearBudget();
		string budget_string = "BUDGET = $" + to_string(pGame->budget) + " | Animals buying: $100 | Water buying: $20";
		pGame->printBudget(budget_string);

		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> distx(range_min_x, range_max_x);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> disty(range_min_y, range_max_y);

		point p;
		p.x = distx(gen1);
		p.y = disty(gen2);

		foodList[count] = new FoodArea(pGame, p, 80, 80, "images\\grass.jpg");
		foodList[count]->draw();
		pGame->foodList[pGame->foodListSize++] = foodList[count];
		count++;
	}
}
Budgetbar::Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height)
	: Drawable(r_pGame, r_point, r_width, r_height)
{
	iconsImages[ICON_CHICK] = "images\\chick.jpg";
	iconsImages[ICON_COW] = "images\\cow.jpg";
    iconsImages[ICON_WATER] = "images\\water.jpg";
	point p;
	p.x = 0;
	p.y = config.toolBarHeight;

	iconsList = new BudgetbarIcon * [ANIMAL_COUNT];
	iconsList[ICON_CHICK] = new ChickIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_CHICK]);
	p.x += config.iconWidth;
	iconsList[ICON_COW] = new CowIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_COW]);
	p.x += config.iconWidth;
	iconsList[ICON_WATER] = new WaterIcon(pGame, p, config.iconWidth, config.toolBarHeight,iconsImages[ICON_WATER]);
    p.x += config.iconWidth;
}

Budgetbar::~Budgetbar()
{
	for (int i = 0; i < ANIMAL_COUNT; i++)
		delete iconsList[i];
	delete[] iconsList;
}

void Budgetbar::draw() const
{
	for (int i = 0; i < ANIMAL_COUNT; i++)
		iconsList[i]->draw();

	window* pWind = pGame->getWind();
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, 2 * config.toolBarHeight, pWind->GetWidth(), 2 * config.toolBarHeight);
}

bool Budgetbar::handleClick(int x, int y)
{
	if (x >= ANIMAL_COUNT * config.iconWidth)
		return false;

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();
	return false;
}
