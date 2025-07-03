#include "pch.h"
#include "GameEndContainer.h"
#include "Sprite.h"

GameEndContainer::GameEndContainer()
{
	SetSize({ 683, 384 });
	_sprite = ResourceManager::GET_SINGLE()->GetSprite(L"Banner_GameEnd");
}

GameEndContainer::~GameEndContainer()
{
}

void GameEndContainer::BeginPlay()
{
    Super::BeginPlay();

}

void GameEndContainer::Tick()
{
    Super::Tick();
}

void GameEndContainer::Render(HDC hdc)
{
    Super::Render(hdc);

    // 화면 중앙에 50% 투명한 검은 배경
    Utils::DrawRectTransparent(
        hdc,
        { GWinSizeX / 2, GWinSizeY / 2 },
        static_cast<int>(GWinSizeX),
        static_cast<int>(GWinSizeY),
        RGB(0, 0, 0),
        128
    );

    if (_sprite)
    {
        int drawX = static_cast<int>(_pos.x - GetSize().x / 2);
        int drawY = static_cast<int>(_pos.y - GetSize().y / 2);

        ::StretchBlt(
            hdc,
            drawX,
            drawY,
            GetSize().x,
            GetSize().y,
            _sprite->GetDC(),
            _sprite->GetPos().x,
            _sprite->GetPos().y,
            _sprite->GetSize().x,
            _sprite->GetSize().y,
            SRCCOPY
        );
    }
}

