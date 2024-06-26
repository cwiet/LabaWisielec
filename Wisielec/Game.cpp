#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std; 

void Game::LoadWordsFromFile(const string& filename) {
	ifstream file(filename);
	string word;
	while (file >> word) {
		m_wordsPool.push_back(word);
	}
	file.close();
}

void Game::OnInit()
{
	m_guessedLetters.clear();
	m_gameState = GameState::START;
	m_lives = 6;

	LoadWordsFromFile("words.txt"); // Nazwa pliku z wyrazami

	if (m_wordsPool.empty()) {
		cerr << "Brak slow w pliku!" << endl;
		return;
	}

	srand(static_cast<unsigned int>(time(NULL)));
	int randomIndex = rand() % m_wordsPool.size();
	m_word = m_wordsPool[randomIndex];

	m_guessedLetters.resize(m_word.length(), false);
}

void Game::OnInput()
{
	cout << "Podaj litere: ";
	cin >> m_lastGuess;
	m_lastGuess = tolower(m_lastGuess);
}

bool Game::OnUpdate(float deltaTime)
{
	bool correctGuess = false;
	for (size_t i = 0; i < m_word.length(); ++i) {
		if (m_word[i] == m_lastGuess) {
			m_guessedLetters[i] = true;
			correctGuess = true;
		}
	}

	if (!correctGuess) {
		m_lives--;
	}

	bool wordGuessed = all_of(m_guessedLetters.begin(), m_guessedLetters.end(), [](bool guessed) { return guessed; });

	if (wordGuessed) {
		cout << "Gratulacje! Odgadles slowo: " << m_word << endl;
		m_gameState = GameState::FINISH;
		return true;
	}

	if (m_lives <= 0) {
		cout << "Koniec gry! Przegrales. Slowo to: " << m_word << endl;
		m_gameState = GameState::FINISH;
		return true;
	}
	
	return false;
}

void Game::OnRender()
{
	cout << "Slowo: ";
	for (size_t i = 0; i < m_word.length(); ++i) {
		if (m_guessedLetters[i]) {
			cout << m_word[i];
		}
		else {
			cout << "_";
		}
	}
	cout << "\nPozostale zycia: " << m_lives << endl;
}

void Game::OnShutdown()
{
	m_guessedLetters.clear();
	m_wordsPool.clear();
}
