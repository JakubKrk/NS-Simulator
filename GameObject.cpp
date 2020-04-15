#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const char* texturesheet)
{
	objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update()
{
	calcPos();
	calcDestRect();
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}


void GameObject::SetSize(int W, int H) {
	SizeH = H; SizeW = W;
}
void GameObject::SetPos(int X, int Y) {
	PosX = X; PosY = Y;
}
void GameObject::SetVel(int X, int Y) {
	VelX = X; VelY = Y;
}


void GameObject::calcPos() {

	PosX = PosX + VelX;
	PosY = PosY + VelY;

}

void GameObject::calcDestRect() {

	destRect.x = PosX - (SizeW / 2);
	destRect.y = PosY - (SizeH / 2);
	destRect.w = SizeW;
	destRect.h = SizeH;

}
