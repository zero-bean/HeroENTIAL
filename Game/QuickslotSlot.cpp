#include "pch.h"
#include "QuickslotSlot.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"
#include "InputManager.h"

QuickslotSlot::QuickslotSlot()
{
	SetSize({ 48, 48 });
}

QuickslotSlot::~QuickslotSlot()
{
}

void QuickslotSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

void QuickslotSlot::Tick()
{
	if (IsMouseInRect()) {
		// 슬롯을 클릭했는지 . . .
		if (!isClicked && InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE))
		{
			if (_onClick)
				_onClick(shared_from_this());
		}
	}

	isClicked = InputManager::GET_SINGLE()->GetButtonDown(KeyType::LEFT_MOUSE);
}

void QuickslotSlot::Render(HDC hdc)
{
	Super::Render(hdc);
}

void QuickslotSlot::UseItem()
{
	if (shared_ptr<Item>* ownerPtr = GetOwnerPtr())
	{
		if (*ownerPtr)
		{
			(*ownerPtr)->Use();

			if ((*ownerPtr)->GetItemCount() <= 0)
			{
				*ownerPtr = nullptr;
			}
		}
	}
}

