#include "pch.h"
#include "ShopSlot.h"
#include "Inventory.h"
#include "Item.h"
#include "Button.h"
#include "Font.h"
ShopSlot::ShopSlot() 
{
    SetSize({ 500, 100 }); // 슬롯 사이즈 고정

    // font
    _font = ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont32");

    // button
    _button = make_shared<Button>();
    _button->SetSize({ 64, 64 });
    _button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Accept"), BS_Default);
    _button->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Accept_Pressed"), BS_Pressed);
}

ShopSlot::~ShopSlot()
{
	_button = nullptr;
    _font = nullptr;
}

void ShopSlot::BeginPlay()
{
    auto self = shared_from_this();

    // 버튼
    const Vec2Int slotSize = GetSize();
    const Vec2 slotPos = GetPos();
    const float buttonX = slotPos.x + slotSize.x / 2 - _button->GetSize().x / 2 - 10.0f;
    _button->SetPos({ buttonX, slotPos.y });
    _button->AddOnClickDelegate([this]() {
        SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
        if (GameManager::GET_SINGLE()->GetInventory()->GetGold() >= _item->GetPrice())
        {
            GameManager::GET_SINGLE()->GetInventory()->AddItem(_item);
            GameManager::GET_SINGLE()->GetInventory()->SetGold(GameManager::GET_SINGLE()->GetInventory()->GetGold() - _item->GetPrice());
        }
        });
	_button->SetEnabled(true);
	_button->SetVisible(true);

    Super::BeginPlay();
}

void ShopSlot::Tick()
{
    Super::Tick();

    if (_button->GetEnabled())
        _button->Tick();
}

void ShopSlot::Render(HDC hdc)
{
    Super::Render(hdc);

    if (_item)
    {
        const Vec2 slotPos = GetPos();
        const float leftX = slotPos.x - GetSize().x / 2 + 10;
        float textY = slotPos.y - 15;

        // 아이템 이름
        Utils::DrawTextColored(hdc, { leftX, textY }, _item->GetItemContent().name, _font->GetHandle(), RGB(255, 255, 0));

        // 아이템 가격
        wstring priceStr = L"가격: " + to_wstring(_item->GetPrice()) + L"G";
        Utils::DrawTextColored(hdc, { leftX + 100.f, textY }, priceStr, _font->GetHandle(), RGB(155, 215, 0));
    }

    if (_button->GetVisible())
        _button->Render(hdc);
}
