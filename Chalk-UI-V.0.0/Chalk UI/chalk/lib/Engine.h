#pragma once

struct UI_Engine {
public:
	void pause();
	void unpause();
	void render();
	void tick();
	// returns the absolute uptime in seconds.
	// the uptime is updated regardless even if the engine is paused.
	void getUptime();
private:
	bool isPaused = false;
	double uptime;
};