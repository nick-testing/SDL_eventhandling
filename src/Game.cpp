#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Checks for errors in surface allocation
static bool checkSurface(const SDL_Surface* surface) {
    if (nullptr == surface) {
        std::cerr << "Surface loading failed. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

Game::Game(): 
    window(nullptr), 
    screenSurface(nullptr),
    currentSurface(nullptr) {}

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
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                std::cerr << "SDL_Image initialization failed, error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                screenSurface = SDL_GetWindowSurface(window);
            }
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
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    SDL_Surface* optimizedSurface = nullptr;

    if (checkSurface(loadedSurface)) {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

void Game::EventHandler() {
    currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_Event e;
    SDL_Rect stretchRect;
    bool quit = false;

    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;
    
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                quit = true;
            }
            else if (SDL_MOUSEBUTTONDOWN == e.type) {
                currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_MOUSE];
            }
            else if (SDL_KEYDOWN == e.type) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                    currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_UP];
                    break;

                    case SDLK_DOWN:
                    currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;

                    case SDLK_LEFT:
                    currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;
                    
                    case SDLK_RIGHT:
                    currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;

                    default:
                    currentSurface = keyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
            
            // Update surface with appropriate image
            //SDL_BlitSurface(currentSurface, nullptr, screenSurface, nullptr);

            SDL_BlitScaled(currentSurface, nullptr, screenSurface, &stretchRect);
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
    
    // Quit SDL_Image subsystems
    IMG_Quit();
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