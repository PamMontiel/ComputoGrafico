#include "GameStateManager.h"
#include <iostream>
GameStateManager* GameStateManager::ptr;

GameStateManager::GameStateManager()
{
	platform = Platform::GetPtr();
}

GameStateManager::~GameStateManager()
{
}

GameStateManager* GameStateManager::GetPtr()
{
	if (ptr == nullptr)
	{
		ptr = new GameStateManager();
	}
	return ptr;
}

void GameStateManager::GameLoop()
{
	//Para que el juego se cierre al poner ESC
	while (!platform->shouldWindowClose())
	{
		try
		{
			if (states.size() == 0)
				throw std::exception("Error");
			auto state = states.top();
			if (state == nullptr)
			{
				break;
			}
			platform->CheckEvent(state, &GameState::Input, &GameState::MouseInput);
			state->Update();
			state->Draw();

		}
		catch (...)
		{
			std::cout << "Critical error App is closing";
			break;
		}
	}
}

void GameStateManager::SetState(GameState* state)
{
	state->Init();
	states.push(state);
}

void GameStateManager::RealaseState()
{
	auto state = states.top();
	state->Close();
	states.pop();
}