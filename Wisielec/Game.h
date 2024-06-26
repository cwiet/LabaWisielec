#pragma once
#include <string>
#include <vector>


class Game
{
	enum class GameState
	{
		START,
		UPDATE,
		FINISH
	};

public:
	void OnInit();
	void OnInput();
	bool OnUpdate(float deltaTime);
	void OnRender();
	void OnShutdown();

private:
	void LoadWordsFromFile(const std::string& filename);
	std::string m_word;
	std::vector<std::string> m_wordsPool;
	std::vector<bool> m_guessedLetters;
	GameState m_gameState = GameState::START;
	int m_lives = 6;
	char m_lastGuess = '\0';

};