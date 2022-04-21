#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <windows.h>

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
	virtual ~TreeState() {}
	/*std::string GetName() const
	{
		return name;
	}*/
	//virtual void Grow(std::unique_ptr<Tree> state, uint16_t deltaTime) = 0;
	virtual void Grow(Tree* state, uint16_t deltaTime) {};
	virtual void DrawCurState(double x, double y) {};
};
//===============================================================
class Tree : public DynamicObject
{
private:
	//std::unique_ptr<TreeState> state;
	TreeState* state;
	uint16_t birth_time;
public:
	Tree(TreeState* state_)
		: state(state_) {
		birth_time = GetTickCount64();
	}
	~Tree() {}

	void Move(uint16_t time) override
	{
		//cout << "Freezing " << state->GetName() << "..." << endl;
		
		state->Grow(this, 60);
	}
	
	void SetState(TreeState* s)
	{
		//cout << "Chaging state from " << state->GetName()
			//<< " to " << s->GetName() << "..." << endl;
		//delete state;
		state = s;
	}
	void Draw() const override;
	TreeState* GetState() const
	{
		return state;
	}
	uint16_t Getbirth_time() const { return birth_time; }
};
class SmallTree : public TreeState
{
public:
	SmallTree() : TreeState() {}
	~SmallTree() override {};

	void Grow(Tree* state, uint16_t deltaTime) override;
	void DrawCurState(double x, double y) override;
};
//===============================================================
class MiddleTree : public TreeState
{
public:
	MiddleTree() : TreeState() {}
	~MiddleTree() override{};
	virtual void Grow(Tree* state, uint16_t deltaTime);
	void DrawCurState(double x, double y) override;
};
//===============================================================
class BigTree : public TreeState
{
public:
	BigTree() : TreeState() {}
	~BigTree() override {};

	virtual void Grow(Tree* state, uint16_t deltaTime);
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
