#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "MyTools.h"

#include "DynamicObject.h"

class Tree;
class LiquidState;
class GasState;
//===============================================================
class TreeState
{
	std::string name;
public:
	TreeState(const std::string& name) : name(name) { }
	std::string GetName() const
	{
		return name;
	}
	virtual void Grow(std::unique_ptr<Tree> state, uint16_t deltaTime) = 0;
	virtual void DrawCurState(double x, double y) = 0;
};
//===============================================================
class Tree : public DynamicObject
{
private:
	std::unique_ptr<TreeState> state;
	//TreeState* state;
public:
	//Tree(TreeState* state)
	Tree(std::unique_ptr<TreeState> state)
		: state(std::move(state)) {}
	~Tree() {}

	void Move(uint16_t time) override
	{
		//cout << "Freezing " << state->GetName() << "..." << endl;
		state->Grow(std::make_unique<Tree>(this), time);
	}
	
	void SetState(std::unique_ptr<TreeState> s)
	{
		//cout << "Chaging state from " << state->GetName()
			//<< " to " << s->GetName() << "..." << endl;
		//delete state;
		state = std::move(s);
	}
	/*std::unique_ptr<TreeState> GetState()
	{
		return state;
	}*/
	
};
class SmallTree : public TreeState
{
public:
	SmallTree() : TreeState("Small") {}
	void Grow(std::unique_ptr<Tree> state, uint16_t deltaTime) override;
	void DrawCurState(double x, double y) override;
};
//===============================================================
class MiddleTree : public TreeState
{
public:
	MiddleTree() : TreeState("Middle") {}
	virtual void Grow(std::unique_ptr<Tree> state, uint16_t deltaTime);
	void DrawCurState(double x, double y) override;
};
//===============================================================
class BigTree : public TreeState
{
public:
	BigTree() : TreeState("Big") {}
	virtual void Grow(std::unique_ptr<Tree> state, uint16_t deltaTime);
	void DrawCurState(double x, double y) override;
};


//===============================================================
/*
��������� ���������� � ���� SBomber
������ : ����������� ������, ������� � �������� ������� �����.
������ �������� 3 ��������� : ����������, ��������, ��������.

+�������� ����� Tree, ��������� ������ DynamicObject.
+���� �� ����� ����� ����� StateContext : �� ����� �������� ��������� �� ������� ��������� � ������� ����� /
+��������� ���������.

�������� ��������� �������� TreeState : SmallTree, MiddleTree, BigTree.
� ����������� ����������� ������� Grow, ������� ����� �������� DeltaTime.
������� ���, ����� ������ ��������� ������������, ��������, 3 �������, � ������ �������� �� ���������.
���������� BigTree ����� ��������.

������� Grow ������ ���������� �� ����������� ������� Move ������ Tree.
����� ���������� ���������� ��������� ������� Tree �� ��������� �����������
��������� ������.�� ���� ������� SmallTree, MiddleTree � BigTree ����� �������
��������� �������� ���������.
*/
