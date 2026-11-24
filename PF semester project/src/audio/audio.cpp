#include "audio.h"
#include <SFML/Audio.hpp>

// Objects ki jagah sirf pointers global hain (nullptr se shuru).
// Asal objects loadAudio() ke andar bante hain, main() shuru hone ke baad.
static sf::SoundBuffer* clickBuffer = nullptr;
static sf::SoundBuffer* winBuffer = nullptr;
static sf::SoundBuffer* loseBuffer = nullptr;
static sf::SoundBuffer* drawBuffer = nullptr;
static sf::Sound* clickSound = nullptr;
static sf::Sound* winSound = nullptr;
static sf::Sound* loseSound = nullptr;
static sf::Sound* drawSound = nullptr;
static int enabled = 1;

int loadAudio()
{
	// Dobara call ho to naye objects na banayein
	if (clickBuffer == nullptr)
	{
		clickBuffer = new sf::SoundBuffer;
		winBuffer = new sf::SoundBuffer;
		loseBuffer = new sf::SoundBuffer;
		drawBuffer = new sf::SoundBuffer;
		clickSound = new sf::Sound;
		winSound = new sf::Sound;
		loseSound = new sf::Sound;
		drawSound = new sf::Sound;
	}

	int loaded = 0;
	loaded += clickBuffer->loadFromFile("assets/sounds/click.wav");
	loaded += winBuffer->loadFromFile("assets/sounds/win.wav");
	loaded += loseBuffer->loadFromFile("assets/sounds/lose.wav");
	loaded += drawBuffer->loadFromFile("assets/sounds/draw.wav");
	clickSound->setBuffer(*clickBuffer);
	winSound->setBuffer(*winBuffer);
	loseSound->setBuffer(*loseBuffer);
	drawSound->setBuffer(*drawBuffer);
	return loaded == 4;
}

void setSoundEnabled(int value) { enabled = value != 0; }
int getSoundEnabled() { return enabled; }
void playClickSound() { if (enabled && clickSound) clickSound->play(); }
void playWinSound() { if (enabled && winSound) winSound->play(); }
void playLoseSound() { if (enabled && loseSound) loseSound->play(); }
void playDrawSound() { if (enabled && drawSound) drawSound->play(); }