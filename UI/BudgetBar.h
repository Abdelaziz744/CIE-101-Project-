#pragma once
#include "../Core/Drawable.h"
#include "../Entities/Animal.h"
#include "../Config/GameConfig.h"
#include <random>
#include <limits>

const int range_min_x = 50;
const int range_max_x = config.windWidth - 50;
const int range_min_y = (config.toolBarHeight * 2) + 50;
const int range_max_y = config.windHeight - config.statusBarHeight - 50;

class BudgetbarIcon : public Drawable
{
public:
	string image_path;
	BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
	virtual void onClick() = 0;
};

class ChickIcon : public BudgetbarIcon
{
public:
	ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
};
class CowIcon : public BudgetbarIcon
{
public:
	CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
};
class WaterIcon : public BudgetbarIcon
{
public:
	FoodArea** foodList;
	int count = 0;
	WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
};

enum ANIMAL_ICONS
{
	ICON_CHICK,
	ICON_COW,
    ICON_WATER,
	ANIMAL_COUNT
};

class Budgetbar : public Drawable
{
private:
	BudgetbarIcon** iconsList;
	string iconsImages[ANIMAL_COUNT];

public:
	Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height);
	~Budgetbar();
	void draw() const override;
	bool handleClick(int x, int y);
};
