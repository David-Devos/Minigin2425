#if _DEBUG
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
#include "InputManager.h"
#include "GameActorCommand.h"
#include "GameActorCommands.h"
#include "ControllableComponent.h"
#include "HealthComponent.h"
#include "HealthObserver.h"
#include "PelletObserver.h"
#include "PelletEatComponent.h"
#include <ServiceLocator.h>
#include <glm.hpp>
#include "PlayerStateComponent.h"
#include "StateMachine.h"
#include "GridComponent.h"
#include "SnoBeeComponent.h"
#include "PushableComponent.h"
#include <iostream>
#include <fstream>
#include <string>

const int LEVEL_WIDTH = 13;
const int LEVEL_HEIGHT = 15;


void loadLevel(const std::string& filename, dae::Scene& scene) {
	std::ifstream file(filename);
	std::string line;
	int y = 0;



	auto gridObj = std::make_shared<dae::GameObject>();
	gridObj->SetLocalPosition(16, 16);
	gridObj->SetTransformDirtyFlag();
	auto gridComp = std::make_unique<dae::GridComponent>(gridObj.get(), LEVEL_WIDTH, LEVEL_HEIGHT, 32.f);

	const int playerHP = 3;
	//UI
	auto font = dae::ResourceManager::GetInstance().LoadFont("pengo-arcade.otf", 12);
	auto healthDisplayObj = std::make_shared<dae::GameObject>();
	auto scoreDisplayObj = std::make_shared<dae::GameObject>();
	auto healthTextComponent = std::make_unique<dae::TextComponent>("Player Health: " + std::to_string(playerHP), font, healthDisplayObj.get());
	auto scoreTextComponent = std::make_unique<dae::TextComponent>("Player Score: 0", font, scoreDisplayObj.get());
	healthTextComponent->SetPosition(0, 150);
	scoreTextComponent->SetPosition(0, 170);

	if (!file.is_open()) {
		std::cerr << "Failed to open level file.\n";
		return;
	}
	std::shared_ptr<dae::GameObject> gameObj;
	std::unique_ptr<dae::PushableComponent> pushableComp;
	std::unique_ptr<dae::HealthObserver> healthObserver;
	std::unique_ptr<dae::PelletObserver> scoreObserver;
	std::unique_ptr<dae::HealthComponent> healthComponent;
	std::unique_ptr<dae::PelletEatComponent> scoreComponent;
	std::unique_ptr<dae::ControllableComponent> snobeeContrComp;
	std::unique_ptr<dae::PlayerStateComponent> stateComp;
	while (std::getline(file, line) && y < LEVEL_HEIGHT) {

		for (int x = 0; x < LEVEL_WIDTH && x < int(line.size()); ++x) {
			switch (line[x]) {
			case 'B':
				gameObj = std::make_shared<dae::GameObject>();
				gameObj->AddComponent(std::make_unique<dae::RenderComponent>(gameObj.get()));
				gameObj->GetComponent<dae::RenderComponent>()->SetTexture("Block.png");
				gameObj->AddComponent(std::make_unique<dae::ControllableComponent>(gameObj.get(), 100.f, dae::GridType::Block, gridComp.get()));
				pushableComp = std::make_unique<dae::PushableComponent>(gameObj.get(), gridComp.get(), glm::vec2{ x,y });
				pushableComp->BindCommand(std::make_tuple(1.f, 0.f), std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ 1.f,0.f }));
				pushableComp->BindCommand(std::make_tuple(-1.f, 0.f), std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ -1.f,0.f }));
				pushableComp->BindCommand(std::make_tuple(0.f, 1.f), std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ 0.f,1.f }));
				pushableComp->BindCommand(std::make_tuple(0.f, -1.f), std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ 0.f,-1.f }));
				gameObj->AddComponent(std::move(pushableComp));
				gridComp->AddGridlockedGO(gameObj.get(), x, y, dae::GridType::Block);
				scene.Add(gameObj);
				break;
			case 'P':
				gameObj = std::make_shared<dae::GameObject>();
				gameObj->AddComponent(std::make_unique<dae::RenderComponent>(gameObj.get()));
				gameObj->GetComponent<dae::RenderComponent>()->SetTexture("Pengo1.png");
				gameObj->AddComponent(std::make_unique<dae::ControllableComponent>(gameObj.get(), 100.f, dae::GridType::Pengo, gridComp.get()));

				//State
				stateComp = std::make_unique<dae::PlayerStateComponent>(gameObj.get(), std::make_shared<dae::StandingState>());
				gameObj->AddComponent(std::move(stateComp));
				//Rest of UI 
				healthObserver = std::make_unique<dae::HealthObserver>(gameObj.get());
				scoreObserver = std::make_unique<dae::PelletObserver>(gameObj.get());
				healthComponent = std::make_unique<dae::HealthComponent>(gameObj.get(), playerHP, healthTextComponent.get());
				scoreComponent = std::make_unique<dae::PelletEatComponent>(gameObj.get(), 0, scoreTextComponent.get());
				healthDisplayObj->AddComponent(std::move(healthTextComponent));
				scoreDisplayObj->AddComponent(std::move(scoreTextComponent));
				healthComponent->AddObserver(healthObserver.get());
				scoreComponent->AddObserver(scoreObserver.get());
				gameObj->AddComponent(std::move(healthComponent));
				gameObj->AddComponent(std::move(scoreComponent));
				healthDisplayObj->AddComponent(std::move(healthObserver));
				scoreDisplayObj->AddComponent(std::move(scoreObserver));

				// inputs
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_UP, std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ 0,-1 }));
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_DOWN, std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ 0,1 }));
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_LEFT, std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ -1,0 }));
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_RIGHT, std::make_unique<MoveCommand>(gameObj.get(), glm::vec2{ 1,0 }));

				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_K, std::make_unique<DamageCommand>(gameObj.get()));
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_I, std::make_unique<PelletEatCommand>(gameObj.get()));
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_G, std::make_unique<TempSoundCommand>(gameObj.get()));
				dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_E, std::make_unique<PushCommand>(gameObj.get()));

				gridComp->AddGridlockedGO(gameObj.get(), x, y, dae::GridType::Pengo);
				scene.Add(gameObj);
				break;
			case 'S':
				gameObj = std::make_shared<dae::GameObject>();
				gameObj->AddComponent(std::make_unique<dae::RenderComponent>(gameObj.get()));
				gameObj->GetComponent<dae::RenderComponent>()->SetTexture("snobee.png");
				snobeeContrComp = std::make_unique<dae::ControllableComponent>(gameObj.get(), 100.f, dae::GridType::SnoBee, gridComp.get());
				gameObj->AddComponent(std::make_unique<dae::SnoBeeComponent>(gameObj.get(), snobeeContrComp.get(), gridComp.get()));
				gameObj->AddComponent(std::move(snobeeContrComp));
				gridComp->AddGridlockedGO(gameObj.get(), x, y, dae::GridType::SnoBee);
				scene.Add(gameObj);
				break;
			default:
				break;
			}
		}
		++y;
	}
	gridObj->AddComponent(std::move(gridComp));
	scene.Add(healthDisplayObj);
	scene.Add(scoreDisplayObj);
	scene.Add(gridObj);

	file.close();
}

void load()
{
	//#if _DEBUG
		//encapsulate in logging sound system in debug using macros
	dae::ServiceLocator::RegisterSoundSystem(
		std::make_unique<dae::SDLSoundSystem>());

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	//for now when and where sounds are loaded, are ill handled
	ss.loadSound("../Data/Explosion.wav", 0);
	ss.loadSound("../Data/PengoTheme.mp3", 1);
	ss.playSound(1, 10);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_shared<dae::GameObject>();
	background->AddComponent(std::make_unique<dae::RenderComponent>(background.get()));
	background->GetComponent<dae::RenderComponent>()->SetTexture("EmptyMap.png");
	scene.Add(background);

	loadLevel("../Data/Level1.txt", scene);

	auto font = dae::ResourceManager::GetInstance().LoadFont("pengo-arcade.otf", 12);
	auto fps = std::make_shared<dae::GameObject>();
	auto fpsTextComponent = std::make_unique<dae::TextComponent>("0 FPS", font, fps.get());

	fps->AddComponent(std::move(fpsTextComponent));
	fps->AddComponent(std::make_unique<dae::FpsComponent>(fps->GetComponent<dae::TextComponent>(), fps.get()));
	scene.Add(fps);



}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}