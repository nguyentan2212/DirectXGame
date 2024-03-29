#include "GameEngine.h"
#include <fstream>
#include "../Graphic/Graphic.h"
#include "../Graphic/TextureService.h"
#include "../Graphic/SpriteService.h"
#include "../Graphic/AnimationService.h"
#include "../Utils/json.hpp"
#include "../Utils/Debug.h"
#include "../Physic/CollisionManager.h"
#include "../Game/Mario/Mario.h"
#include "KeyboardHandler.h"
#include "Camera.h"
#include "Scene.h"

using json = nlohmann::json;

GameEngine* GameEngine::_instance = nullptr;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

GameEngine::GameEngine()
{

}

GameEngine* GameEngine::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new GameEngine();
    }
    return _instance;
}

void GameEngine::Init(HINSTANCE hInstance, int nCmdShow)
{
    this->_hInstance = hInstance;
    
    // Load config file
    fstream file(DEFAULT_CONFIG);
    json config = json::parse(file);

    this->_fps = config["fps"].get<float>();
    this->_width = config["window"]["width"].get<int>();
    this->_height = config["window"]["height"].get<int>();
    
    // Create window depend on loaded config
    CreateGameWindow(nCmdShow);

    // Init keyboard handler
    KeyboardHandler* keyboardHandler = KeyboardHandler::GetInstance();
    keyboardHandler->Initialize(this->_hInstance, this->_hwnd);

    // Init graphic
    Graphic* graphic = Graphic::GetInstance();
    graphic->Init(this->_hwnd, (int)this->_fps);

    // Init texture service
    TextureService* textures = TextureService::GetInstance();
    textures->Init(config["textures"]);

    // Init sprite service. MUST AFTER TEXTURE SERVICE INIT
    SpriteService* sprites = SpriteService::GetInstance();
    // Load sprite sheets for textures
    sprites->Init(config["textures"]);

    // Init animation service. MUST AFTER SPRITE SERVICE
    AnimationService* animations = AnimationService::GetInstance();
    animations->Init(config["animations"]);

    // Init camera
    Camera* camera = Camera::GetInstance();
    camera->Init(config["window"]["width"].get<float>(), config["window"]["height"].get<float>());

    // Timer begin
    this->_timer = new Timer(this->_fps);
    this->_timer->Start();
}

void GameEngine::Run()
{
    while (ProcessMessages())
    {
        float delta = 0;
        if (this->_timer->Tick(delta))
        {
            Update(delta);
        }
        Render();
    }
}

void GameEngine::AddScene(Scene* scene, UINT sceneId)
{
    this->_scenes[sceneId] = scene;
    scene->context = this;
}

void GameEngine::TransitionTo(UINT sceneId)
{
    Scene* scene = this->_scenes[sceneId];
    if (scene == nullptr)
    {
        DebugOut((wchar_t*)L"[ERROR] Scene transition to NULL");
        return;
    }
    UINT preSceneId = -1;
    if (this->_currentScene != nullptr)
    {
        preSceneId = this->_currentScene->sceneId;
    }
    this->_currentScene = scene;
    this->_currentScene->OnChanged(preSceneId);
}

void GameEngine::Update(float deltaTime)
{
    if (this->_currentScene == nullptr)
    {
        return;
    }
    this->_currentScene->Update(deltaTime);
}

void GameEngine::Render()
{
    if (this->_currentScene == nullptr)
    {
        return;
    }
    Graphic* graphic = Graphic::GetInstance();
    graphic->Begin();
    graphic->BeginSprite();
    // Begin draw sprites
    this->_currentScene->Render();
    // End draw sprites
    graphic->EndSprite();
    // Begin draw boxes
    this->_currentScene->DrawBoundingBox();
    // End draw boxes
    graphic->End();
}

void GameEngine::CreateGameWindow(int nCmdShow)
{
    WNDCLASS wc = {};

    wc.lpfnWndProc = WinProc;
    wc.hInstance = this->_hInstance;
    wc.lpszClassName = GAME_TITLE;
    RegisterClass(&wc);

    // Create the window.

    this->_hwnd = CreateWindowEx(
        0,                    // Optional window styles.
        GAME_TITLE, // Window class
        GAME_TITLE, // Window text
        WS_OVERLAPPEDWINDOW,  // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, this->_width, this->_height,

        NULL,      // Parent window
        NULL,      // Menu
        this->_hInstance, // Instance handle
        NULL       // Additional application data
    );

    if (this->_hwnd == NULL)
    {
        return;
    }

    ShowWindow(this->_hwnd, nCmdShow);
    UpdateWindow(this->_hwnd);
    SetDebugWindow(this->_hwnd);

    return;
}

bool GameEngine::ProcessMessages()
{
    // Run the message loop.
    MSG msg = {};
    if (PeekMessage(&msg,       // Where to store message (if one exists) See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
        this->_hwnd, // Handle to window we are checking messages for
        0,          // Minimum Filter Msg Value - We are not filtering for specific messages, but the min/max could be used to filter only mouse messages for example.
        0,          // Maximum Filter Msg Value
        PM_REMOVE)) // Remove message after capturing it via PeekMessage. For more argument options, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
    {
        TranslateMessage(&msg); // Translate message from virtual key messages into character messages so we can dispatch the message. See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644955(v=vs.85).aspx
        DispatchMessage(&msg);  // Dispatch message to our Window Proc for this window. See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644934(v=vs.85).aspx
    }
    return true;
}

GameEngine::~GameEngine()
{
    delete this->_hInstance;
    delete this->_timer;
}
