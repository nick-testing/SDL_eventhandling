#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

Game::Game(): 
    window(nullptr), 
    screenSurface(nullptr), 
    imgSurface(nullptr) {}

bool Game::Init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL: Initialization failed. Error: " << SDL_GetError() << std::endl;
        success = false;
    } 
    else {
        // Create window
        window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "SDL: window creation failed. Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            success = false;
        }
        else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool Game::LoadMedia() {
    bool success = true;

    // Load image
    imgSurface = SDL_LoadBMP("assets/helloworld.bmp");
    if (!imgSurface) {
        std::cerr << "SDL: window creation failed. Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

void Game::Close() {
    // Deallocate surface
    SDL_FreeSurface(imgSurface);
    imgSurface = nullptr;
    
    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void Game::Run() {
    if (!Init())
        std:: cerr << "Initialization failed";
    else {
        if (!LoadMedia())
            std::cerr << "Media loading failed" << std::endl;
        else
            EventHandler();
    }

    Close();
}