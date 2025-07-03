#include "pch.h"
#include "UIManager.h"
#include "GameUI.h"
#include "UI.h"
#include "Panel.h"

void UIManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void UIManager::BeginPlay()
{
	// 1. 요청된 객체 추가 작업을 처리 후,
	ProcessAddUI();

	// 2. UI 객체 초기화
	for (shared_ptr<UI> ui : _uis)
		ui->BeginPlay();
}

void UIManager::Update()
{
	// 1. 요청된 UI 추가 작업을 진행하고, 
	ProcessAddUI();
	
	// 2. UI Tick 실행
	for (shared_ptr<UI> ui : _uis)
	{
		if (ui->GetEnabled())
			ui->Tick();
	}

	// 3. 요청된 UI 삭제 작업을 진행한다
	ProcessRemoveUI();
}

void UIManager::Render(HDC hdc)
{
	for (shared_ptr<UI> ui : _uis)
	{
		if (ui->GetVisible())
			ui->Render(hdc);
	}
}

void UIManager::Clear()
{
	_drag = {};

	while (!_addQueue.empty()) 
		_addQueue.pop();

	while (!_removeQueue.empty()) 
		_removeQueue.pop();
	
	_uis.clear();
}

void UIManager::HandleInputs()
{
	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::ESC))
	{
		auto main = FindUI<SettingsMainPanel>();
		auto sound = FindUI<SettingsSoundPanel>();

		if (sound && sound->GetVisible())
		{
			sound->SetVisible(false);
			sound->SetEnabled(false);
		}
		else if (main)
		{
			main->SetVisible(!main->GetVisible());
			main->SetEnabled(main->GetVisible());
		}
	}

	if (InputManager::GET_SINGLE()->GetButtonDown(KeyType::I))
	{
		if (shared_ptr<InventoryPanel> inven = FindUI<InventoryPanel>())
		{
			inven->SetEnabled(!inven->GetEnabled());
			inven->SetVisible(!inven->GetVisible());

			// 인벤토리 닫으면 
			if (!inven->GetVisible())
			{
				// 드래그 정보 초기화
				DragState& drag = UIManager::GET_SINGLE()->GetDragState();
				drag.EndDrag();
			}
		}
	}
}

void UIManager::AddUI(shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_addQueue.push(ui);
}

void UIManager::RemoveUI(shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_removeQueue.push(ui);
}

bool UIManager::IsMouseInUIs()
{
	for (const shared_ptr<UI>& ui : _uis)
	{
		if (const shared_ptr<Panel> panel = dynamic_pointer_cast<Panel>(ui))
		{
			const vector<shared_ptr<UI>> children = panel->GetChildren();
			for (const shared_ptr<UI>& child : children)
			{
				if (child->IsMouseInRect() && ui->GetVisible())
					return true;
			}
		}

		if (ui->IsMouseInRect() && ui->GetVisible())
			return true;
	}

	return false;
}

void UIManager::ProcessAddUI()
{
	while (!_addQueue.empty())
	{
		const shared_ptr<UI> target = _addQueue.front();
		_addQueue.pop();

		if (target)
			_uis.push_back(target);
	}
}

void UIManager::ProcessRemoveUI()
{
	while (!_removeQueue.empty())
	{
		const shared_ptr<UI> target = _removeQueue.front();
		_removeQueue.pop();

		// 삭제할 대상을 찾고,
		auto it = find(_uis.begin(), _uis.end(), target);
		// 발견했다면,
		if (it != _uis.end())
		{
			// 마지막 요소의 소유권을 뺏고,
			*it = move(_uis.back());
			// 비어있는 마지막 요소는 삭제
			_uis.pop_back();
		}
	}
}
