#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// For the love of god optimize and refactor this code - this is a proof of concept

// instead of sizeof probably should just store array size as a const 

// do math stuff between frames - in the kill time loop? would  need to finish executing code before breaking loop
// Go over datatypes, might be mixing floats and ints. Check whether uints are correct size
// Make functions if necessary - avoid global variables

// Sprites AND cells references are hard coded at the moment. This algo will be given the number of elements as a param

// Instead of generating random values, generate some ramping with an offset of 20 and just insert randomly into cells

// Need counter of counter. one that counts through the numbers to be compared, one that keeps track of the sweep

int main()
{
	// Counter of which element 
	uint8_t counter = 0;

	const unsigned int vWidth = 800;
	const unsigned int vHeight = 600;
	const float barWidth = 20.f;
	// 5 = gap between bars, elementCount = vWidth / (barWidth + 5)
	const unsigned int elementCount = 32;
	// 
	vector <Sprite> spriteVect;
	//
	uint32_t dataSet[elementCount];
	// Generate random numbers for the data set
	// srand(time(NULL));
	for (uint16_t i = 0; i < elementCount; i++) {
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
	for (uint16_t i = 0; i < elementCount; i++) {
		Sprite pillar;
		pillar.setTextureRect(IntRect(0, 0, barWidth, dataSet[i]));
		pillar.setTexture(texture);
		// Origin set to bottom left, origin should be constant and not re calculated. Maybe just change position of sprite
		pillar.setOrigin(0, dataSet[i]);
		pillar.setPosition((i * barWidth) + (i * 5), vHeight);
		// Passes a class of Sprite to vector?
		spriteVect.push_back(pillar);
	}

	// Ask user which algo to use

	// Needs to show initial data set <--

	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		// here or before event?
		clock.restart();

		// just update the heights? instead of position, would need to change origin too though
		// or change the positions OR order of sprites in vector and then draw that 

		if (dataSet[counter] > dataSet[(counter) + 1]) {
			// Swap Numbers, else they're already in order
			uint32_t saveNr = dataSet[(counter) + 1];		// Store lower nr of 2nd cell
			dataSet[counter + 1] = dataSet[counter];
			dataSet[counter] = saveNr;
			// Array is updated - next update visual representation (position) of the array
			// Sprites will not be in order representative of the order of the array
			/**/

			spriteVect[counter].setPosition(((counter + 1) * barWidth) + ((counter + 1) * 5), vHeight);
			spriteVect[counter + 1].setPosition((counter * barWidth) + (counter * 5), vHeight);
			
			// Set position of get position? - this is going nowhere
			/*
			Vector2f spritePos = spriteVect[counter].getPosition();
			//
			spriteVect[counter + 1].setPosition(spriteVect[counter].getPosition());
			spriteVect[counter].setPosition(spriteVect[counter].getPosition());
			*/
			// Alternative - change position as they are rendered? - wouldn't affect position

			// Change order of sprites in Sprite vector:

		}
		// Do nothing?

		// repeat, could place this in the for below
		// Separate each iteration of the data set/array
		cout << "NEW" << "\n";
		for (uint8_t i = 0; i < elementCount; i++) {
			cout << dataSet[i] << "\n";
		}

		window.clear();
		for (uint16_t i = 0; i < spriteVect.size(); i++) {
			window.draw(spriteVect[i]);
		}
		window.display();

		// If not at end of array, increment
		// Probably better to have a "true" incremental counter and then just make a temp var with the * 2 offset
		if (counter < (elementCount - 2)) { // (elementCount - 2) as it was trying to access out of bounds
			counter += 2;
		}// Break? - seems like bad practise. FIX THIS 
		else if (){
			
		}
		else {
			return 0;
		}

		// To do work in this loop have an AND that the "computeDone" flag/bool is set
		while (clock.getElapsedTime() < milliseconds(1000)) {
			// Kill any remaining time
			;
		}
	}

	return 0;
}