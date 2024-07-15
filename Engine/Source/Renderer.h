#pragma once

#include <SDL.h>
#include <iostream>



class Renderer {

public:
	Renderer() = default;
	//functions
	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string name, int width, int height);
	void BeginFrame();
	void EndFrame();

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);

	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);

	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	
	
protected:

private:
	//variables
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	int m_width;
	int m_height;
};