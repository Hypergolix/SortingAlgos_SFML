#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	// Algo 1
	bool odd = true;

	const unsigned int vWidth = 800;
	const unsigned int vHeight = 600;
	const float barWidth = 20.f;
	// 5 = gap between bars, elementCount = vWidth / (barWidth + 5)
	const unsigned int elementCount = 32;
	// 
	vector <Sprite> spriteVect;
	//
	uint32_t dataSet[elementCount];
	// A way to check if its done
	uint32_t dataSetOld[elementCount];

	// Generate random numbers for the data set
	srand(time(NULL));
	for (uint32_t i = 0; i < elementCount; i++) {
		dataSet[i] = rand() % 400 + 10;
		cout << dataSet[i] << "\n";
	}
	cout << "FIRST^" << "\n"; // Just separate the initial print out from the rest

	RenderWindow window(VideoMode(vWidth, vHeight), "SUS");
	// "pillars"
	Texture texture;
	// Create texture to allow for max size pillar
	if (!texture.create(barWidth, vHeight)) {
		// Error
	}
	// Change to white texture
	sf::Uint8* pixels = new sf::Uint8[barWidth * vHeight * 4]; // * 4 because pixels have 4 components (RGBA)
	// Update texture
	texture.update(pixels);
	// Create sprites to represent size of each element in the data set
	for (uint32_t i = 0; i < elementCount; i++) {
		Sprite pillar;
		pillar.setTextureRect(IntRect(0, 0, barWidth, dataSet[i]));
		pillar.setTexture(texture);
		// Origin set to bottom left, origin should be constant and not re calculated. Maybe just change position of sprite. (i * barWidth) + (i * 5)
		pillar.setOrigin(0, dataSet[i]);
		pillar.setPosition((i * barWidth), vHeight);
		// Passes a class of Sprite to vector? 
		spriteVect.push_back(pillar);
	}

	// Ask user which algo to use

	// Needs to show initial data set <--

	Clock clock;
	while (window.isOpen())
	{
		// Couldn't this be placed just for rendering timing? no way to accurately time frames then?
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		// Could make more efficient by ignoring "set numbers"/nums in order
		for (uint32_t i = 0; i < (elementCount - 1); i++) {
			// If leftmost is larger than right, swap them
			if (dataSet[i] > dataSet[i + 1]) {
				clock.restart();
				// Save value of rightmost cell
				uint32_t saveNr = dataSet[i + 1];
				// Transfer leftMost to rightMost cell
				dataSet[i + 1] = dataSet[i];
				// Transfer rightMost to leftMost
				dataSet[i] = saveNr;
				// Draw sprites in order that they appear in vector?

				// set position based on where it appears in array

				// Update visual positions - function?
				// Get xPos, then increase or decrease its position by the width of the sprite

				// store then set, 

				// position as identifier? - its the way its accessing based on [i] in the spriteVect

				float storeLeft = spriteVect[i].getPosition().x;

				spriteVect[i].setPosition((spriteVect[i + 1].getPosition().x), vHeight);
				// 2nd
				spriteVect[i + 1].setPosition(storeLeft, vHeight);
				// change position based on its current position +/- barWidth, can add back the + 5 gap if needed

				// Seems like a bad solution - should the sprite vector really be used for indexing
				Sprite swapSprite;
				swapSprite = spriteVect[i];
				spriteVect[i] = spriteVect[i + 1];
				spriteVect[i + 1] = swapSprite;


				// Draw etc
				// Print current array
				cout << "NEW" << "\n";
				for (uint32_t i = 0; i < elementCount; i++) {
					cout << dataSet[i] << "\n";
				}

				// Draw call - this draws AFTER changes have been made, no initial 
				window.clear();
				for (uint32_t i = 0; i < spriteVect.size(); i++) {
					// Change position of sprite here?
					window.draw(spriteVect[i]);
				}
				window.display();

				while (clock.getElapsedTime() < milliseconds(33)) {
					// Kill any remaining time
					;
				}
			}
		}

	}

	return 0;
}