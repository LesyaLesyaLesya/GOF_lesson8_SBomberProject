#include "Tree.h"
void Tree::Draw() const
{
	state->DrawCurState(this->GetX(), this->GetY());
}
void SmallTree::Grow(Tree* state, uint16_t deltaTime)
{
	uint16_t curTime = GetTickCount64();
	if ((state->Getbirth_time() - curTime)% deltaTime == 0)
	{
		state->SetState(new MiddleTree());
		DrawCurState(state->GetX(), state->GetY());
	}	
}
void MiddleTree::Grow(Tree* state, uint16_t deltaTime)
{
	if ((state->Getbirth_time() - GetTickCount64()) % deltaTime == 0)
	{
		state->SetState(new BigTree());
		DrawCurState(state->GetX(), state->GetY());
	}
}
void BigTree::Grow(Tree* state, uint16_t deltaTime)
{
	if ((state->Getbirth_time() - GetTickCount64()) % deltaTime == 0)
	{
		DrawCurState(state->GetX(), state->GetY());
	}
}
void SmallTree::DrawCurState(double x, double y)
{
	MyTools::SetColor(MyTools::CC_LightGreen);
	MyTools::GotoXY(x, y);
	std::cout << "**";
	MyTools::GotoXY(x, y-1);
	std::cout << "**";
	MyTools::GotoXY(x, y - 1);
	std::cout << "**";
}
void MiddleTree::DrawCurState(double x, double y)
{
	MyTools::SetColor(MyTools::CC_LightGreen);
	MyTools::GotoXY(x, y);
	std::cout << "**";
	MyTools::GotoXY(x, y - 1);
	std::cout << "**";
	MyTools::GotoXY(x, y - 1);
	std::cout << "**";
	//*****************************
	MyTools::SetColor(MyTools::CC_LightGreen);
	MyTools::GotoXY(x-1, y-3);
	std::cout << "*****";
	MyTools::GotoXY(x - 2, y - 4);
	std::cout << "******";
	MyTools::GotoXY(x-1, y-5);
	std::cout << "****";
}
void BigTree::DrawCurState(double x, double y)
{
	MyTools::SetColor(MyTools::CC_LightGreen);
	MyTools::GotoXY(x, y);
	std::cout << "**";
	MyTools::GotoXY(x, y - 1);
	std::cout << "**";
	MyTools::GotoXY(x, y - 1);
	std::cout << "**";
	//*******************************
	MyTools::SetColor(MyTools::CC_LightGreen);
	MyTools::GotoXY(x - 1, y - 3);
	std::cout << "*****";
	MyTools::GotoXY(x - 2, y - 4);
	std::cout << "******";
	MyTools::GotoXY(x - 1, y - 5);
	std::cout << "****";
	//*******************************
	MyTools::SetColor(MyTools::CC_LightRed);
	MyTools::GotoXY(x, y-6);
	std::cout << "@";
	MyTools::GotoXY(x-2, y - 3);
	std::cout << "@";
}			
		  