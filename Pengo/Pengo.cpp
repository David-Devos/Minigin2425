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

	// We'll keep the fps counter for now
	auto font = dae::ResourceManager::GetInstance().LoadFont("pengo-arcade.otf", 12);
	auto fps = std::make_shared<dae::GameObject>();
	auto fpsTextComponent = std::make_unique<dae::TextComponent>("0 FPS", font, fps.get());

	fps->AddComponent(std::move(fpsTextComponent));
	fps->AddComponent(std::make_unique<dae::FpsComponent>(fps->GetComponent<dae::TextComponent>(), fps.get()));
	scene.Add(fps);


	//tutorial
	font = dae::ResourceManager::GetInstance().LoadFont("pengo-arcade.otf", 12);
	auto howToPlay = std::make_shared<dae::GameObject>();
	auto textComponent = std::make_unique<dae::TextComponent>("P1 arrows movement, K to take damage, I to eat pellets", font, howToPlay.get());
	textComponent->SetPosition(0, 100);
	howToPlay->AddComponent(std::move(textComponent));
	textComponent = std::make_unique<dae::TextComponent>("P2 WASD movement, L to take damage, O to eat pellets", font, howToPlay.get());
	textComponent->SetPosition(0, 120);
	howToPlay->AddComponent(std::move(textComponent));
	textComponent = std::make_unique<dae::TextComponent>("Press G to test soundeffect or make a player die", font, howToPlay.get());
	textComponent->SetPosition(0, 140);
	howToPlay->AddComponent(std::move(textComponent));
	scene.Add(howToPlay);

	const int playerHP = 3;
	//UI
	auto healthDisplayObj = std::make_shared<dae::GameObject>();
	auto scoreDisplayObj = std::make_shared<dae::GameObject>();
	auto healthTextComponent = std::make_unique<dae::TextComponent>("Player Health: " + std::to_string(playerHP), font, healthDisplayObj.get());
	auto scoreTextComponent = std::make_unique<dae::TextComponent>("Player Score: 0", font, scoreDisplayObj.get());
	//Debug
	auto debugGridObj = std::make_shared<dae::GameObject>();
	debugGridObj->SetLocalPosition(8, 8);
	debugGridObj->SetTransformDirtyFlag();
	auto debugGridComp = std::make_unique<dae::GridComponent>(debugGridObj.get(), 13, 15, 32.f);
	auto debugGridRenderComp = std::make_unique<dae::RenderComponent>(debugGridObj.get());
	debugGridRenderComp->SetTexture("sun.png");

	auto debugGridBlock = std::make_shared<dae::GameObject>();
	debugGridBlock->AddComponent(std::make_unique<dae::RenderComponent>(debugGridBlock.get()));
	debugGridBlock->GetComponent<dae::RenderComponent>()->SetTexture("Block.png");
	debugGridBlock->AddComponent(std::make_unique<dae::ControllableComponent>(debugGridBlock.get(), 100.f, dae::GridType::Block, debugGridComp.get()));
	auto pushableComp = std::make_unique<dae::PushableComponent>(debugGridBlock.get(), debugGridComp.get(), glm::vec2{ 4,5 });
	pushableComp->BindCommand(std::make_tuple(1.f, 0.f), std::make_unique<MoveCommand>(debugGridBlock.get(), glm::vec2{1.f,0.f})); 
	pushableComp->BindCommand(std::make_tuple(-1.f, 0.f), std::make_unique<MoveCommand>(debugGridBlock.get(), glm::vec2{ -1.f,0.f }));
	pushableComp->BindCommand(std::make_tuple(0.f, 1.f), std::make_unique<MoveCommand>(debugGridBlock.get(), glm::vec2{ 0.f,1.f })); 
	pushableComp->BindCommand(std::make_tuple(0.f, -1.f), std::make_unique<MoveCommand>(debugGridBlock.get(), glm::vec2{ 0.f,-1.f }));
	debugGridBlock->AddComponent(std::move(pushableComp));

	auto debugGridBlock2 = std::make_shared<dae::GameObject>();
	debugGridBlock2->AddComponent(std::make_unique<dae::RenderComponent>(debugGridBlock2.get()));
	debugGridBlock2->GetComponent<dae::RenderComponent>()->SetTexture("Block.png");
	debugGridBlock2->AddComponent(std::make_unique<dae::ControllableComponent>(debugGridBlock2.get(), 100.f, dae::GridType::Block, debugGridComp.get()));
	auto pushableComp2 = std::make_unique<dae::PushableComponent>(debugGridBlock2.get(), debugGridComp.get(), glm::vec2{ 0,5 });
	pushableComp2->BindCommand(std::make_tuple(1.f, 0.f), std::make_unique<MoveCommand>(debugGridBlock2.get(), glm::vec2{ 1.f,0.f }));
	pushableComp2->BindCommand(std::make_tuple(-1.f, 0.f), std::make_unique<MoveCommand>(debugGridBlock2.get(), glm::vec2{ -1.f,0.f }));
	pushableComp2->BindCommand(std::make_tuple(0.f, 1.f), std::make_unique<MoveCommand>(debugGridBlock2.get(), glm::vec2{ 0.f,1.f }));
	pushableComp2->BindCommand(std::make_tuple(0.f, -1.f), std::make_unique<MoveCommand>(debugGridBlock2.get(), glm::vec2{ 0.f,-1.f }));
	debugGridBlock2->AddComponent(std::move(pushableComp2));
	

	//Player1
	auto player1Obj = std::make_shared<dae::GameObject>();
	player1Obj->AddComponent(std::make_unique<dae::RenderComponent>(player1Obj.get()));
	player1Obj->GetComponent<dae::RenderComponent>()->SetTexture("Pengo1.png");
	player1Obj->AddComponent(std::make_unique<dae::ControllableComponent>(player1Obj.get(), 100.f, dae::GridType::Pengo, debugGridComp.get()));
	player1Obj->SetLocalPosition(300, 200);
	player1Obj->SetGlobalPosition(300, 200);

	//Rest of UI
	healthTextComponent->SetPosition(0, 150);
	scoreTextComponent->SetPosition(0, 170);
	auto healthObserver = std::make_unique<dae::HealthObserver>(player1Obj.get());
	auto scoreObserver = std::make_unique<dae::PelletObserver>(player1Obj.get());
	auto healthComponent = std::make_unique<dae::HealthComponent>(player1Obj.get(), playerHP, healthTextComponent.get());
	auto scoreComponent = std::make_unique<dae::PelletEatComponent>(player1Obj.get(), 0, scoreTextComponent.get());
	healthDisplayObj->AddComponent(std::move(healthTextComponent));
	scoreDisplayObj->AddComponent(std::move(scoreTextComponent));
	healthComponent->AddObserver(healthObserver.get());
	scoreComponent->AddObserver(scoreObserver.get());
	player1Obj->AddComponent(std::move(healthComponent));
	player1Obj->AddComponent(std::move(scoreComponent));
	healthDisplayObj->AddComponent(std::move(healthObserver));
	scoreDisplayObj->AddComponent(std::move(scoreObserver));
	//Debug 
	auto debugStateComp = std::make_unique<dae::PlayerStateComponent>(player1Obj.get(), std::make_shared<dae::StandingState>());
	player1Obj->AddComponent(std::move(debugStateComp));

	auto snobeeTestObj = std::make_shared<dae::GameObject>();
	snobeeTestObj->AddComponent(std::make_unique<dae::RenderComponent>(snobeeTestObj.get()));
	snobeeTestObj->GetComponent<dae::RenderComponent>()->SetTexture("sun.png");
	auto snobeeContrComp = std::make_unique<dae::ControllableComponent>(snobeeTestObj.get(), 100.f, dae::GridType::SnoBee, debugGridComp.get());
	snobeeTestObj->AddComponent(std::make_unique<dae::SnoBeeComponent>(snobeeTestObj.get(), snobeeContrComp.get()));
	debugGridComp->AddGridlockedGO(player1Obj.get(), 5, 5, dae::GridType::Pengo);
	snobeeTestObj->AddComponent(std::move(snobeeContrComp));
	debugGridObj->AddComponent(std::move(debugGridComp));
	debugGridObj->AddComponent(std::move(debugGridRenderComp));
	scene.Add(debugGridBlock);
	scene.Add(debugGridBlock2);
	scene.Add(debugGridObj);
	scene.Add(snobeeTestObj);

	//End Debug
	scene.Add(player1Obj);
	scene.Add(healthDisplayObj);
	scene.Add(scoreDisplayObj);


	//Input
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_UP, std::make_unique<MoveCommand>(player1Obj.get(), glm::vec2{ 0,-1 }));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_DOWN, std::make_unique<MoveCommand>(player1Obj.get(), glm::vec2{ 0,1 }));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_LEFT, std::make_unique<MoveCommand>(player1Obj.get(), glm::vec2{ -1,0 }));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_RIGHT, std::make_unique<MoveCommand>(player1Obj.get(), glm::vec2{ 1,0 }));

	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_K, std::make_unique<DamageCommand>(player1Obj.get()));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_I, std::make_unique<PelletEatCommand>(player1Obj.get()));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_G, std::make_unique<TempSoundCommand>(player1Obj.get()));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_E, std::make_unique<PushCommand>(player1Obj.get()));



	//UI
	healthDisplayObj = std::make_shared<dae::GameObject>();
	scoreDisplayObj = std::make_shared<dae::GameObject>();
	healthTextComponent = std::make_unique<dae::TextComponent>("Player Health: " + std::to_string(playerHP), font, healthDisplayObj.get());
	scoreTextComponent = std::make_unique<dae::TextComponent>("Player Score: 0", font, scoreDisplayObj.get());

	//Player2
	auto player2Obj = std::make_shared<dae::GameObject>();
	player2Obj->AddComponent(std::make_unique<dae::RenderComponent>(player2Obj.get()));
	player2Obj->GetComponent<dae::RenderComponent>()->SetTexture("Pengo2.png");
	player2Obj->AddComponent(std::make_unique<dae::ControllableComponent>(player2Obj.get(), 100.f, dae::GridType::Pengo));
	player2Obj->SetLocalPosition(300, 200);
	player2Obj->SetGlobalPosition(300, 200);

	//Rest of UI
	healthTextComponent->SetPosition(0, 200);
	scoreTextComponent->SetPosition(0, 220);
	healthObserver = std::make_unique<dae::HealthObserver>(player2Obj.get());
	scoreObserver = std::make_unique<dae::PelletObserver>(player2Obj.get());
	healthComponent = std::make_unique<dae::HealthComponent>(player2Obj.get(), playerHP, healthTextComponent.get());
	scoreComponent = std::make_unique<dae::PelletEatComponent>(player2Obj.get(), 0, scoreTextComponent.get());
	healthDisplayObj->AddComponent(std::move(healthTextComponent));
	scoreDisplayObj->AddComponent(std::move(scoreTextComponent));
	healthComponent->AddObserver(healthObserver.get());
	scoreComponent->AddObserver(scoreObserver.get());
	player2Obj->AddComponent(std::move(healthComponent));
	player2Obj->AddComponent(std::move(scoreComponent));
	healthDisplayObj->AddComponent(std::move(healthObserver));
	scoreDisplayObj->AddComponent(std::move(scoreObserver));
	scene.Add(player2Obj);
	scene.Add(healthDisplayObj);
	scene.Add(scoreDisplayObj);

	//Input
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_W, std::make_unique<MoveCommand>(player2Obj.get(), glm::vec2{ 0,-1 }));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_S, std::make_unique<MoveCommand>(player2Obj.get(), glm::vec2{ 0,1 }));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_A, std::make_unique<MoveCommand>(player2Obj.get(), glm::vec2{ -1,0 }));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Down, SDL_SCANCODE_D, std::make_unique<MoveCommand>(player2Obj.get(), glm::vec2{ 1,0 }));

	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_L, std::make_unique<DamageCommand>(player2Obj.get()));
	dae::InputManager::GetInstance().BindCommand(dae::KeyState::Tapped, SDL_SCANCODE_O, std::make_unique<PelletEatCommand>(player2Obj.get()));


}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}