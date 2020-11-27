#include "PowerUpInventory.h"

PowerUpInventory::PowerUpInventory(Game* game)
{
	slots.push_back(new UIPowerUp(0.1 * WIDTH, 0.92 * HEIGHT, game));
	slots.push_back(new UIPowerUp(0.17 * WIDTH, 0.92 * HEIGHT, game));
}

void PowerUpInventory::draw()
{
	for (auto const& slot : slots) {
		slot->draw();
	}
}

UIPowerUp* PowerUpInventory::getSlot(float x, float y)
{
	for (auto const& slot : slots) {
		if (slot->containsPoint(x, y)) {
			return slot;
		}
	}

	return nullptr;
}

void PowerUpInventory::addPowerUp(PowerUp* powerUp)
{
	for (auto const& slot : slots) {
		if (slot->empty()) {
			slot->setPowerUp(powerUp);
			return;
		}
	}
}

bool PowerUpInventory::isFull() {
	bool full = true;
	for (auto const& slot : slots) {
		if (slot->empty())
			full = false;
	}
	return full;
}
