#include "SampleScene.h"

#include "DummyEntity.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateEntity<DummyEntity>(50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::EventType::KeyPressed) {
        sf::Vector2f direction(0.f, 0.f);

        if (event.key.code == sf::Keyboard::Key::Z ) {
			if (event.key.code == sf::Keyboard::Key::D) {
				direction.x += 10; // Déplacement vers la droite
				direction.y -= 10; // Déplacement vers le haut
			}			
            if (event.key.code == sf::Keyboard::Key::Q) {
                direction.x -= 10; // Déplacement vers la droite
                direction.y -= 10; // Déplacement vers le haut
            }
            direction.y -= 10; // Déplacement vers le haut
        }

        if (event.key.code == sf::Keyboard::Key::S) {
            if (event.key.code == sf::Keyboard::Key::D) {
                direction.x += 10; // Déplacement vers la droite
                direction.y += 10; // Déplacement vers le haut
            }
            else if (event.key.code == sf::Keyboard::Key::Q) {
                direction.x -= 10; // Déplacement vers la droite
                direction.y += 10; // Déplacement vers le haut
            }
            else {
                direction.y += 10; // Déplacement vers le bas
            }
        }
        if (event.key.code == sf::Keyboard::Key::Q) {
            direction.x -= 10; // Déplacement vers la gauche
        }
        if (event.key.code == sf::Keyboard::Key::D) {
            direction.x += 10; // Déplacement vers la droite
        }

        if (event.type == sf::Event::EventType::KeyReleased) {
			direction.x = 0.f;
			direction.y = 0.f;
        }

        if (direction.x != 0.f || direction.y != 0.f) {
            pEntitySelected->GoToDirection(pEntitySelected->GetPosition().x + direction.x, pEntitySelected->GetPosition().y + direction.y);
        }

        if (event.key.code == sf::Keyboard::Key::Space) {
            pEntitySelected->SetDirection(0.f, 0.f, 0.f);
        }
    }

    if (event.type != sf::Event::EventType::MouseButtonPressed)
        return;

    if (event.mouseButton.button == sf::Mouse::Button::Right)
    {
        TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
        TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
    }

    if (event.mouseButton.button == sf::Mouse::Button::Left)
    {
        if (pEntitySelected != nullptr)
        {
            pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
        }
    }
}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}