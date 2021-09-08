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

// Compare last dataset to new dataset, if no changes it should be done

// Write some functions, LOTS of repeat code - how to pass vectors etc to functions? avoid global...

int main()
{
	// Algo 1
	// Counter of which element - Algo 1
	uint8_t counter = 0;

	// Algo 2
	uint32_t highNr = 0;
	uint8_t counter2 = 0;

	// Algo 3 - WORKS!

	// Odd numbered elements
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

	vector <uint32_t> dataVector;
	vector <uint32_t> dataVectorSort;

	// Generate random numbers for the data set
	srand(time(NULL));
	for (uint16_t i = 0; i < elementCount; i++) {
		dataSet[i] = rand() % 400 + 10;
		dataVector.push_back(dataSet[i]);
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
		// here or before event?


		// just update the heights? instead of position, would need to change origin too though
		// or change the positions OR order of sprites in vector and then draw that 

		// Algo 3
		// If numbers not in order - CHECK else break
		/**/

		// counter needs to control

		// Do one set of compares each frame
		if (odd) {
			for (uint8_t i = 0; i < elementCount; i += 2) {
				// Couldn't this be placed just for rendering timing? no way to accurately time frames then?
				clock.restart();
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}
				// If leftmost is larger than right, swap them
				if (dataSet[i] > dataSet[i + 1]) { // or -1 to avoid out of bounds, starting for at 1
					// Save value of rightmost cell
					uint32_t saveNr = dataSet[i + 1];
					// Transfer leftMost to rightMost cell
					dataSet[i + 1] = dataSet[i];
					// Transfer rightMost to leftMost
					dataSet[i] = saveNr;
					// Draw sprites in order that they appear in vector?

					// divide by 2?

					// Update visual positions - function?
					spriteVect[i].setTextureRect(IntRect(0, 0, barWidth, dataSet[i]));
					spriteVect[i].setOrigin(0, dataSet[i]);
					spriteVect[i].setPosition((i * barWidth) + (i * 5), vHeight);
					// 2nd
					spriteVect[i + 1].setTextureRect(IntRect(0, 0, barWidth, dataSet[i + 1]));
					spriteVect[i + 1].setOrigin(0, dataSet[i + 1]);
					spriteVect[i + 1].setPosition(((i + 1) * barWidth) + ((i + 1) * 5), vHeight);

					// Draw call - wont show initial now
					window.clear();
					for (uint16_t i = 0; i < spriteVect.size(); i++) {
						// Change position of sprite here?
						window.draw(spriteVect[i]);
					}
					window.display();

					// To do work in this loop have an AND that the "computeDone" flag/bool is set
					while (clock.getElapsedTime() < milliseconds(100)) {
						// Kill any remaining time
						;
					}
				}
			}
		}
		else // Even
		{
			// Just leave 1st and last alone, calculate a "mask" for the middle numbers to be compared
			for (uint8_t i = 1; i < (elementCount - 1); i++) {
				// Couldn't this be placed just for rendering timing? no way to accurately time frames then?
				clock.restart();
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}
				if (dataSet[i] > dataSet[i + 1]) {
					// Save value of rightmost cell
					uint32_t saveNr = dataSet[i + 1];
					// Transfer leftMost to rightMost cell
					dataSet[i + 1] = dataSet[i];
					// Transfer rightMost to leftMost
					dataSet[i] = saveNr;
					// Draw sprites in order that they appear in vector?

					// Update visual positions - function?
					spriteVect[i].setTextureRect(IntRect(0, 0, barWidth, dataSet[i]));
					spriteVect[i].setOrigin(0, dataSet[i]);
					spriteVect[i].setPosition((i * barWidth) + (i * 5), vHeight);
					// 2nd
					spriteVect[i + 1].setTextureRect(IntRect(0, 0, barWidth, dataSet[i + 1]));
					spriteVect[i + 1].setOrigin(0, dataSet[i + 1]);
					spriteVect[i + 1].setPosition(((i + 1) * barWidth) + ((i + 1) * 5), vHeight);

					// Draw call
					window.clear();
					for (uint16_t i = 0; i < spriteVect.size(); i++) {
						// Change position of sprite here?
						window.draw(spriteVect[i]);
					}
					window.display();

					// To do work in this loop have an AND that the "computeDone" flag/bool is set
					while (clock.getElapsedTime() < milliseconds(100)) {
						// Kill any remaining time
						;
					}
				}

			}
		}
		// Toggle odd = ~odd;
		if (odd) {
			odd = false;
			// reset counter?
		}
		else {
			odd = true;
			// reset counter?
		}

		// remove cell but move its value/push_back - do other cells move over?

		// push back the new highest nr and also display this by updating positions of the bars

		// Increment counter etc (A2), highlight highest nr (green) and comparisons (red)


		// Do nothing?

		// repeat, could place this in the for below
		// Separate each iteration of the data set/array

		cout << "NEW" << "\n";
		for (uint8_t i = 0; i < elementCount; i++) {
			cout << dataSet[i] << "\n";
		}



		/*
		cout << "NEW" << "\n";
		for (uint8_t i = 0; i < dataVector.size(); i++) {
			cout << dataVector.at(i) << "\n";
		}
		*/

		/*
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
		*/

	}

	return 0;
}