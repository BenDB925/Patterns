#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

//not platform specific
class DrawAPI
{
public:
	virtual void Draw() = 0;
};

//platform specific
class DrawImpl : public DrawAPI
{
public:
	void Draw() override
	{
		cout << "Draw Implementation" << endl;
	}
};

class GraphicProxy : public DrawAPI
{
public:
	GraphicProxy()
	{
		graphic = nullptr;
	}

	~GraphicProxy() {}

	void Draw() override
	{
		getInstance()->Draw();
	}

private:
	DrawImpl * graphic;

	DrawImpl* getInstance(void)
	{
		if (!graphic)
		{
			graphic = new DrawImpl();
		}

		return graphic;
	}
};


class Character 
{
public:
	Character() {}
	virtual ~Character() {}
	virtual void draw() = 0;
};

class Player : public Character
{
public:

	Player(DrawAPI * pAPI)
		:_drawAPI(pAPI) { }

	void draw() override
	{
		_drawAPI->Draw();
	}

private:
	DrawAPI * _drawAPI;
};

class Boss : public Character
{
public:
	void draw() override
	{
		cout << "Draw Boss" << endl;
	}
};


class Factory 
{
public:
	virtual Character* CreatePlayer() = 0;
	virtual Character* CreateOpponents() = 0;
};

class CharacterFactory : public Factory 
{
public:
	Character* CreatePlayer() override
	{
		return new Player(new GraphicProxy());
	}

	Character* CreateOpponents() override
	{
		return new Boss;
	}
};

void DemoAbstractFactory()
{
	Factory* factory = new CharacterFactory;
	vector<Character*> characters;
	characters.push_back(factory->CreatePlayer());
	characters.push_back(factory->CreateOpponents());

	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->draw();
	}
}

int main() 
{
	DemoAbstractFactory();

	system("PAUSE");
}