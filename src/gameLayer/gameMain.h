bool initGame(); // called once in the beginning of the game
bool updateGame(); // called every frame, return false if the game should be closed
void closeGame(); // called once when the game is closing, used to free resources and save data if needed