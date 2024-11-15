#include "SceneManager.h"
#include "Core/Scene.h"

#include <iostream>

void SceneManager::Start()
{
    g_SceneManager = this;
    m_IsRunning = true;
}

void SceneManager::Update(const float dt) const
{
    if(!m_Scenes.empty())
    {
        m_Scenes.back()->Tick(dt);
    }
}

void SceneManager::Shutdown()
{
    if (!m_Scenes.empty())
    {
        m_Scenes.back()->Destroy();
    }

    m_IsRunning = false;
}

void SceneManager::HandleEvents() const
{
    if (!m_Scenes.empty())
    {
        m_Scenes.back()->HandleEvents();
    }
}

void SceneManager::Render() const
{
    if (!m_Scenes.empty())
    {
        m_Scenes.back()->Render();
    }
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    if(newScene != nullptr)
    {
        //Remove current state
        RemoveScene();

        //Add new scene to the back
        m_Scenes.push_back(std::move(newScene));
        m_Scenes.back()->Init();
    }
    else
    {
        std::cout << "Invalid Scene passed";
        return;
    }
}

//Removes last scene (LIFO)
void SceneManager::RemoveScene()
{
    //Remove current state
    if (!m_Scenes.empty())
    {
        //call Shutdown for current state before removal to clean up.
        m_Scenes.back()->Destroy();
        m_Scenes.pop_back();
    }
}

SceneManager* SceneManager::GetSceneManager()
{
    return g_SceneManager;
}

bool SceneManager::IsRunning() const
{
    return m_IsRunning;
}
