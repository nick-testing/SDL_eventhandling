#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>

// Checks for errors in surface allocation
static bool checkSurface(const SDL_Surface* surface) {
    if (surface == nullptr) {
        std::cerr << "Surface loading failed. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

Game::Game(): 
    window(nullptr), 
    screenSurface(nullptr) {}

bool Game::Init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL: Initialization failed. Error: " << SDL_GetError() << std::endl;
        success = false;
    } 
    else {
        // Create window
        window = SDL_CreateWindow("Input Response", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    keyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assets/default.bmp");
    success = checkSurface(keyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT]);

    keyPressedSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/up.bmp");
    success = checkSurface(keyPressedSurfaces[KEY_PRESS_SURFACE_UP]);

    keyPressedSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/down.bmp");
    success = checkSurface(keyPressedSurfaces[KEY_PRESS_SURFACE_DOWN]);

    keyPressedSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/left.bmp");
    success = checkSurface(keyPressedSurfaces[KEY_PRESS_SURFACE_LEFT]);

    keyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/right.bmp");
    success = checkSurface(keyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT]);

    keyPressedSurfaces[KEY_PRESS_SURFACE_MOUSE] = loadSurface("assets/mouse.bmp");
    success = checkSurface(keyPressedSurfaces[KEY_PRESS_SURFACE_MOUSE]);

    return success;
}

SDL_Surface* Game::loadSurface(const char* path) {
    return SDL_LoadBMP(path);
}

void Game::EventHandler() {
    SDL_Event e;
    bool quit = false; 
    
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                
            }
      
            // Update surface with appropriate image
            // SDL_BlitSurface(imgSurface, nullptr, screenSurface, nullptr);

            SDL_UpdateWindowSurface(window);
        } 
    }
}

void Game::Close() {
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(keyPressedSurfaces[i]);
        keyPressedSurfaces[i] = nullptr;
    }
    
    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void Game::Run() {
    if (!Init()) {
        std:: cerr << "Initialization failed";
    }
    else {
        LoadMedia();
        EventHandler();
    }

    Close();
}