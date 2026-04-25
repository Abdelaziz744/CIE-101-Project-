#include "Warehouse.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include <string>
using namespace std;

Warehouse::Warehouse(Game* r_pGame, point r_point, int r_width, int r_height)
	: Drawable(r_pGame, r_point, r_width, r_height), numProducts(0)
{
}

Warehouse::~Warehouse()
{
	for (int i = 0; i < numProducts; i++)
		delete products[i];
}

void Warehouse::addProductType(string name, int price)
{
	if (numProducts < 10)
		products[numProducts++] = new Product(name, price);
}

void Warehouse::addProduct(string name)
{
	for (int i = 0; i < numProducts; i++)
	{
		if (products[i]->name == name)
		{
			products[i]->count++;
			draw();
			return;
		}
	}
}

int Warehouse::sellProduct(string name)
{
	for (int i = 0; i < numProducts; i++)
	{
		if (products[i]->name == name)
		{
			int earned = products[i]->count * products[i]->pricePerUnit;
			products[i]->count = 0;
			draw();
			return earned;
		}
	}
	return 0;
}

void Warehouse::draw() const
{
	window* pWind = pGame->getWind();

	// Background
	pWind->SetPen(DARKGRAY, 2);
	pWind->SetBrush(YELLOW);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + width, RefPoint.y + height);

	// Title
	pWind->SetPen(BLUE, 1);
	pWind->SetFont(16, BOLD, BY_NAME, "Arial");
	pWind->DrawString(RefPoint.x + 10, RefPoint.y + 6, "Warehouse");

	// Separator
	pWind->SetPen(DARKGRAY, 1);
	pWind->DrawLine(RefPoint.x, RefPoint.y + 28, RefPoint.x + width, RefPoint.y + 28);

	// Column headers
	pWind->SetPen(BLACK, 1);
	pWind->SetFont(13, BOLD, BY_NAME, "Arial");
	pWind->DrawString(RefPoint.x + 8, RefPoint.y + 34, "Product");
	pWind->DrawString(RefPoint.x + 110, RefPoint.y + 34, "Qty");
	pWind->DrawString(RefPoint.x + 155, RefPoint.y + 34, "Price");

	pWind->SetPen(DARKGRAY, 1);
	pWind->DrawLine(RefPoint.x, RefPoint.y + 52, RefPoint.x + width, RefPoint.y + 52);

	// Product rows
	pWind->SetFont(13, BOLD, BY_NAME, "Arial");
	for (int i = 0; i < numProducts; i++)
	{
		int rowY = RefPoint.y + 58 + i * 24;

		pWind->SetPen(BLACK, 1);
		pWind->DrawString(RefPoint.x + 8, rowY, products[i]->name);
		pWind->DrawString(RefPoint.x + 110, rowY, "x" + to_string(products[i]->count));
		pWind->DrawString(RefPoint.x + 155, rowY, "$" + to_string(products[i]->pricePerUnit));
	}

	// Border
	pWind->SetPen(DARKGRAY, 2);
	pWind->SetBrush(YELLOW);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + width, RefPoint.y + height);
}

