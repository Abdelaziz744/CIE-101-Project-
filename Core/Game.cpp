#include "Game.h"
#include "../Config/GameConfig.h"
#include "../Entities/Animal.h"
#include <ctime>
#include <windows.h>

Game::Game()
{
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	createToolbar();
	createBudgetbar();

	// Abdelaziz Feature 1 start
	animalCount = 0;
	productCount = 0;
	level = 1;
	goal = 10;
	startTime = time(0);

	for (int i = 0; i < 100; i++)
	{
		animalList[i] = nullptr;
		productList[i] = nullptr;
	}
	// Abdelaziz Feature 1 end

	clearStatusBar();
}

Game::~Game()
{
	// Abdelaziz Feature 1 start
	for (int i = 0; i < animalCount; i++)
		if (animalList[i]) delete animalList[i];

	for (int i = 0; i < productCount; i++)
		if (productList[i]) delete productList[i];
	// Abdelaziz Feature 1 end
}

clicktype Game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);
}

string Game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)
			return "";
		if (Key == 13)
			return Label;
		if (Key == 8)
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

window* Game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}

void Game::createToolbar()
{
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
	gameToolbar->draw();
}

void Game::createBudgetbar()
{
	point budgetbarUpperleft;
	budgetbarUpperleft.x = 0;
	budgetbarUpperleft.y = config.toolBarHeight;

	gameBudgetbar = new Budgetbar(this, budgetbarUpperleft, 0, config.toolBarHeight);
	gameBudgetbar->draw();
}

void Game::clearBudget() const
{
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(config.windWidth - 500, config.toolBarHeight, config.windWidth, 2 * config.toolBarHeight);
}

void Game::printBudget(string msg) const
{
	clearBudget();

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth - 200, config.toolBarHeight + 10, msg);
}

void Game::clearStatusBar() const
{
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}
void Game::updatestatusbar() const
{
	clearStatusBar();
	string status = "Level: " + to_string(level) + " | Timer: " + to_string(time) + " | Animals: " + to_string(animalcount);
	pWind->SetPen(config.penColor);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), status);

}
void Game::drawfieldboundary() const {
	pWind->SetPen(config.penColor, config.penWidth);
	// Draw from below the BudgetBar to above the StatusBar
	pWind->DrawRectangle(0, 2 * config.toolBarHeight, config.windWidth, config.windHeight - config.statusBarHeight, FRAME);
}

void Game::printMessage(string msg) const
{
	clearStatusBar();

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
}

// Abdelaziz Feature 1 start
void Game::updateStatusBar(int elapsedTime) const
{
	clearStatusBar();

	pWind->SetPen(WHITE, 2);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");

	int y = config.windHeight - (int)(0.7 * config.statusBarHeight);

	pWind->DrawString(20, y, "Timer: " + to_string(elapsedTime) + "s");
	pWind->DrawString(260, y, "Goal: " + to_string(goal));
	pWind->DrawString(470, y, "Level: " + to_string(level));
	pWind->DrawString(680, y, "Animals: " + to_string(animalCount));
}

void Game::addAnimal(Animal* pAnim)
{
	if (animalCount < 100 && pAnim)
		animalList[animalCount++] = pAnim;
	else
		delete pAnim;
}

void Game::addProduct(Product* pProd)
{
	if (productCount < 100 && pProd)
		productList[productCount++] = pProd;
	else
		delete pProd;
}

void Game::drawAllAnimals() const
{
	for (int i = 0; i < animalCount; i++)
		if (animalList[i]) animalList[i]->draw();
}

void Game::drawAllProducts() const
{
	for (int i = 0; i < productCount; i++)
		if (productList[i]) productList[i]->draw();
}
// Abdelaziz Feature 1 end

window* Game::getWind() const
{
	return pWind;
}

void Game::go() const
{
	int x, y;
	bool isExit = false;
	bool wasMouseDown = false;

	pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-project) - - - - - - - - - -");
	pWind->SetBuffering(true);

	do
	{
		bool isMouseDown = pWind->GetButtonState(LEFT_BUTTON, x, y);
		if (isMouseDown && !wasMouseDown)
		{
			if (y >= 0 && y < config.toolBarHeight)
			{
				isExit = gameToolbar->handleClick(x, y);
			}
			else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight)
			{
				gameBudgetbar->handleClick(x, y);
			}
		}
		wasMouseDown = isMouseDown;

		// Abdelaziz Feature 1 start
		time_t currentTime = time(0);
		int elapsedTime = (int)(currentTime - startTime);

		for (int i = 0; i < animalCount; i++)
		{
			if (animalList[i])
			{
				animalList[i]->moveStep();
				animalList[i]->produce(currentTime);
			}
		}
		// Abdelaziz Feature 1 end

		pWind->SetBrush(config.bkGrndColor);
		pWind->SetPen(config.bkGrndColor, 1);
		pWind->DrawRectangle(0, 0, config.windWidth, config.windHeight);

		gameToolbar->draw();
		gameBudgetbar->draw();

		// Abdelaziz Feature 4,7,19,21 start

		drawAllAnimals();
		drawAllProducts();
		// Abdelaziz Feature 4,7,19,21 end
	

		string budget_string = "BUDGET = $" + to_string(budget);
		printBudget(budget_string);

		// Abdelaziz Feature 1 start
		updateStatusBar(elapsedTime);
		// Abdelaziz Feature 1 end

		pWind->UpdateBuffer();
		Sleep(20);

	} while (!isExit);
}
