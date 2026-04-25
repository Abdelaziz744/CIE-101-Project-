#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include <ctime>
#include <string>

class Animal;
class Product;

class Game
{
private:
	window* pWind;
	Toolbar* gameToolbar;
	Budgetbar* gameBudgetbar;

	// Abdelaziz Feature 1 start
	Animal* animalList[100];
	int animalCount;
	Product* productList[100];
	int productCount;
	int level;
	int goal;
	time_t startTime;
	// Abdelaziz Feature 1 end

public:
	int budget = 2000;
	Game();
	~Game();

	clicktype getMouseClick(int& x, int& y) const;
	string getSrting() const;

	window* CreateWind(int, int, int, int) const;
	void createToolbar();
	void createBudgetbar();
	void clearBudget() const;
	void printBudget(string msg) const;
	void clearStatusBar() const;
	void printMessage(string msg) const;

	// Abdelaziz Feature 1 start
	void updateStatusBar(int elapsedTime) const;
	void addAnimal(Animal* pAnim);
	void addProduct(Product* pProd);
	void drawAllAnimals() const;
	void drawAllProducts() const;
	// Abdelaziz Feature 1 end

	void go() const;

	window* getWind() const;
};
