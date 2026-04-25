#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include <ctime>
#include <string>
#include "../Entities/FoodArea.h"

class Animal;
class Product;

//magdy
class Warehouse;
class Wolf;
class FoodArea;

class Game
{
private:
	window* pWind;
	Toolbar* gameToolbar;
	Budgetbar* gameBudgetbar;

//magdy
Warehouse*  warehouse;
FoodArea* foodAreas[5];
int       numFoodAreas;
time_t    lastTickTime;     
int       tickCount;    

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
	int level = 1;
	int time = 150;
	int animalcount = 0;
	void gametimer(int level); // The function to calculate time
    int foodListSize = 0;
    FoodArea** foodList;
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
    void updatestatusbar() const; //refresh the status bar continously
	void printMessage(string msg) const;
//magdy
void     createWarehouse();
void     createWolf();
void     createFoodAreas();
void     gameTick();        




	// Abdelaziz Feature 1 start
	void updateStatusBar(int elapsedTime) const;
	void addAnimal(Animal* pAnim);
	void addProduct(Product* pProd);
	void drawAllAnimals() const;
	void drawAllProducts() const;
    void warehouse() const;
	// Abdelaziz Feature 1 end

	void go() const;

	window* getWind() const;
};
