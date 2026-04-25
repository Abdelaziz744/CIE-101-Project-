#pragma once
#include "../Core/Drawable.h"
#include <string>
using namespace std;


struct Product
{
	string name;
	int count;
	int pricePerUnit;   
	Product(string n, int price) : name(n), count(0), pricePerUnit(price) {}
};

class Warehouse : public Drawable
{
private:
	Product* products[10]; 
	int numProducts;
	color bgColor;
public:
	Warehouse(Game* r_pGame, point r_point, int r_width, int r_height);
	~Warehouse();

	void addProductType(string name, int price);  
	void addProduct(string name);                  
	int  sellProduct(string name);                

	virtual void draw() const override;
};
