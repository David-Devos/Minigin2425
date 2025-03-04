#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include <imgui_plot.h>


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_shared<dae::GameObject>();
	background->AddComponent(std::make_unique<dae::RenderComponent>(background.get()));
	background->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	////go->SetTexture("background.tga");
	scene.Add(background);

	auto logo = std::make_shared<dae::GameObject>();
	logo->SetGlobalPosition(216, 180);
	logo->AddComponent(std::make_unique<dae::RenderComponent>(logo.get()));
	logo->GetComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	scene.Add(logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();
	title->SetGlobalPosition(80, 20); 
	title->AddComponent(std::make_unique<dae::TextComponent>("Programming 4 Assignment", font, title.get()));
	//to->SetPosition(80, 20);
	scene.Add(title);

	auto fps = std::make_shared<dae::GameObject>();

	auto textComponent = std::make_unique<dae::TextComponent>("0 FPS", font, fps.get());

	fps->AddComponent(std::move(textComponent));
	fps->AddComponent(std::make_unique<dae::FpsComponent>(fps->GetComponent<dae::TextComponent>(), fps.get()));
	scene.Add(fps);

	//Rotators
	auto sunObj = std::make_shared<dae::GameObject>();
	sunObj->SetGlobalPosition(300, 200);
	sunObj->AddComponent(std::make_unique<dae::RenderComponent>(sunObj.get()));
	sunObj->GetComponent<dae::RenderComponent>()->SetTexture("sun.png");
	scene.Add(sunObj);

	auto earthObj = std::make_shared<dae::GameObject>();
	earthObj->SetParent(sunObj.get(), true);
	earthObj->AddComponent(std::make_unique<dae::RenderComponent>(earthObj.get()));
	earthObj->GetComponent<dae::RenderComponent>()->SetTexture("earth.png");
	earthObj->AddComponent(std::make_unique<dae::RotatorComponent>(earthObj.get(), 3.f, 100.f));
	scene.Add(earthObj);

	auto moonObj = std::make_shared<dae::GameObject>();
	moonObj->SetParent(earthObj.get(), true);
	moonObj->AddComponent(std::make_unique<dae::RenderComponent>(moonObj.get()));
	moonObj->GetComponent<dae::RenderComponent>()->SetTexture("moon.png");
	moonObj->AddComponent(std::make_unique<dae::RotatorComponent>(moonObj.get(), -7.f, 40.f));
	scene.Add(moonObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}