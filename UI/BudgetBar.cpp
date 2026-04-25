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

		// Abdelaziz Feature 4,19,21 start
		pGame->addAnimal(new Chick(pGame, p, 50, 50, image_path));
		// Abdelaziz Feature 4,19,21 end

	}
}
void CowIcon::onClick()
{
	cout << "Icon Cow Clicked" << endl;
	if (pGame->budget > 200) {
		pGame->budget = pGame->budget - 200;
		pGame->clearBudget();
		string budget_string = "BUDGET = $" + to_string(pGame->budget);
		pGame->printBudget(budget_string);

		point p;

		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> distx(range_min_x, range_max_x);
		std::uniform_int_distribution<int> disty(range_min_y, range_max_y);

		p.x = distx(gen);
		p.y = disty(gen);

		cowList[count] = new Cow(pGame, p, 70, 70, image_path);
		cowList[count]->draw();
		count++;
	}

Budgetbar::Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height)
	: Drawable(r_pGame, r_point, r_width, r_height)
{
	iconsImages[ICON_CHICK] = "images\\chick.jpg";

	point p;
	p.x = 0;
	p.y = config.toolBarHeight;

	iconsList = new BudgetbarIcon * [ANIMAL_COUNT];
	iconsList[ICON_CHICK] = new ChickIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_CHICK]);
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
