#pragma once


namespace dimensions {

	constexpr int resolution[] = { 1366, 768 };	//screen resolution
	//constexpr int screenPosition[] = {1000, 768};
	constexpr int platformHeight = resolution[1]/6;		
	constexpr int maxPlatformLength = resolution[0]/4;
	constexpr int minPlatformLength = resolution[0] / 10;

	constexpr int terrainSpawnerX = resolution[0] + maxPlatformLength;
	constexpr int terrainUpperSpawnerY = platformHeight;
	constexpr int terrainMiddleSpawnerY = platformHeight * 3;
	constexpr int terrainLowerSpawnerY = platformHeight * 5;
	constexpr int maxNumOfPlatform = 4;

	constexpr int terrainDestroyerX = 0 - maxPlatformLength;
	constexpr int terrainUpperDestroyerY = terrainUpperSpawnerY;
	constexpr int terrainMiddleDestroyerY = terrainMiddleSpawnerY;
	constexpr int terrainLowerDestroyerY = terrainLowerSpawnerY;

	constexpr int velocity = 50;	//get from Code Monky
}