#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "MyTools.h"

#include "DynamicObject.h"

class Tree;
class SmallTree;
class MiddleTree;
class BigTree;
//===============================================================
class TreeState
{
	//std::string name;
public:
	//TreeState(const std::string& name) : name(name) { }
	TreeState(){}
	~TreeState() {}
	/*std::string GetName() const
	{
		return name;
	}*/
	//virtual void Grow(std::unique_ptr<Tree> state, uint16_t deltaTime) = 0;
	virtual void Grow(std::shared_ptr<Tree> state, uint16_t deltaTime) {};
	virtual void DrawCurState(double x, double y) {};
};
//===============================================================
class Tree : public DynamicObject
{
private:
	//std::unique_ptr<TreeState> state;
	std::shared_ptr<TreeState> state;
	
public:
	Tree(std::shared_ptr<TreeState> state_)
		: state(std::move(state_)){}
	~Tree() {}

	void Move(uint16_t time) override
	{
		//cout << "Freezing " << state->GetName() << "..." << endl;
		state->Grow(std::make_shared<Tree>(this), time);
	}
	
	void SetState(std::shared_ptr<TreeState> s)
	{
		//cout << "Chaging state from " << state->GetName()
			//<< " to " << s->GetName() << "..." << endl;
		//delete state;
		state = s;
	}
	void Draw() const override;
	std::shared_ptr<TreeState> GetState()
	{
		return state;
	}
	
};
class SmallTree : public TreeState
{
public:
	SmallTree() : TreeState() {}
	~SmallTree() override {};

	void Grow(std::shared_ptr<Tree> state, uint16_t deltaTime) override;
	void DrawCurState(double x, double y) override;
};
//===============================================================
class MiddleTree : public TreeState
{
public:
	MiddleTree() : TreeState() {}
	~MiddleTree() override{};
	virtual void Grow(std::shared_ptr<Tree> state, uint16_t deltaTime);
	void DrawCurState(double x, double y) override;
};
//===============================================================
class BigTree : public TreeState
{
public:
	BigTree() : TreeState() {}
	~BigTree() override {};

	virtual void Grow(std::shared_ptr<Tree> state, uint16_t deltaTime);
	void DrawCurState(double x, double y) override;
};


//===============================================================
/*
Применяем «Состояние» в игре SBomber
Задача : реализовать дерево, которое с течением времени растёт.
Дерево проходит 3 состояния : «маленькое», «среднее», «большое».

+Создадим класс Tree, наследник класса DynamicObject.
+Этот же класс будет нашим StateContext : он будет включать указатель на текущее состояние и функцию смены /
+установки состояния.

Создадим отдельную иерархию TreeState : SmallTree, MiddleTree, BigTree.
В нейсоздадим виртуальную функцию Grow, которая будет получать DeltaTime.
Сделаем так, чтобы каждое состояние отображалось, например, 3 секунды, и дальше менялось на следующее.
«Состояние» BigTree будет конечным.

Функция Grow должна вызываться из виртуальной функции Move класса Tree.
Также необходимо пробросить рисование объекта Tree до рисования конкретного
состояния дерева.То есть классам SmallTree, MiddleTree и BigTree нужна функция
рисования текущего состояния.
*/
