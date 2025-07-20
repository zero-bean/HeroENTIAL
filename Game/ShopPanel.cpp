#include "pch.h"
#include "ShopPanel.h"
#include "QuestContainer.h"
#include "ShopSlot.h"
#include "Button.h"
#include "Item.h"

ShopPanel::ShopPanel()
{
    // 패널
    SetSize({ 683, 384 });
    SetPos({ GWinSizeX / 2, GWinSizeY / 2 });

    // 컨테이너
    _container = make_shared<QuestContainer>();
    _container->SetPos(GetPos());
    _container->SetSize({ 683, 384 });
    AddChild(_container);

    // 버튼
    _buttons.resize(2);

    _buttons[0] = make_shared<Button>();
    _buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Arrow_Left"), BS_Default);
    _buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Arrow_Left_Pressed"), BS_Pressed);
    AddChild(_buttons[0]);
    _buttons[1] = make_shared<Button>();
    _buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Arrow_Right"), BS_Default);
    _buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Arrow_Right_Pressed"), BS_Pressed);
    AddChild(_buttons[1]);
}

ShopPanel::~ShopPanel()
{
}

void ShopPanel::BeginPlay()
{
    // 버튼
    auto self = shared_from_this();

    _buttons[0]->SetPos({ GetPos().x - 300, GetPos().y });
    _buttons[0]->SetSize({ 64, 64 });
    _buttons[0]->AddOnClickDelegate([this]() { OnScrollUp(); });

    _buttons[1]->SetPos({ GetPos().x + 300, GetPos().y });
    _buttons[1]->SetSize({ 64, 64 });
    _buttons[1]->AddOnClickDelegate([this]() { OnScrollDown(); });

    // 상점 목록 갱신
    Refresh();

    Super::BeginPlay();
}

void ShopPanel::Tick()
{
    Super::Tick();
}

void ShopPanel::Render(HDC hdc)
{
    Super::Render(hdc);
}

void ShopPanel::Refresh()
{
    // 기존 슬롯 제거
    for (auto& slot : _slots)
        RemoveChild(slot);
    _slots.clear();

    const int slotHeight = 100;
    const int slotStartY = GetPos().y - GetSize().y / 2 + 50;

    int startIdx = _scrollOffset;
    int endIdx = min(startIdx + _visibleSlotCount, static_cast<int>(_items.size()));

    for (int i = startIdx; i < endIdx; ++i)
    {
        auto slot = make_shared<ShopSlot>();
        slot->SetItem(_items[i]);

        const int offsetY = (i - startIdx) * slotHeight;
        const POINT pos = { GetPos().x, slotStartY + offsetY };
        slot->SetPos(pos);

        _slots.push_back(slot);
        slot->BeginPlay();
        AddChild(slot);
    }
}

void ShopPanel::OnScrollUp()
{
    SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");

    if (_scrollOffset > 0)
    {
        _scrollOffset--;
        Refresh();
    }
}

void ShopPanel::OnScrollDown()
{
    SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");

    int itemCount = static_cast<int>(_items.size());
    int maxScrollOffset = max(0, itemCount - _visibleSlotCount);

    if (_scrollOffset < maxScrollOffset)
    {
        _scrollOffset++;
        Refresh();
    }
}