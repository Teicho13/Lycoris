#pragma once
#include <memory>
#include <vector>

class Scene;
class SceneManager
{
public:
    void Start();
    void Update(float dt) const;
    void Render() const;
    void Shutdown();
    void HandleEvents() const;

    void ChangeScene(std::unique_ptr<Scene> newScene);
    void RemoveScene();

    static SceneManager* GetSceneManager();
    bool IsRunning() const;

private:
    bool m_IsRunning = false;
    std::vector<std::unique_ptr<Scene>> m_Scenes;
};

inline SceneManager* g_SceneManager = nullptr;