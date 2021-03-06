#include <iostream>
#include "SDL2/SDL.h"

int main(int argc, char **argv)
{
	// init tools
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("hello world", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; 
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// load asset
	SDL_Surface* img = SDL_LoadBMP("images/image.bmp");
	if (img == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, img);
	if (texture == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_FreeSurface(img);
		std::cout << "SDL_Texture Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// game loop
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, texture, NULL, NULL);
	SDL_RenderPresent(ren);
	SDL_Delay(3000);

	// free memory
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(img);
	SDL_Quit();

	return 0;
}
