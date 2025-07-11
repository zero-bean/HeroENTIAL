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
	// 1. ��û�� ��ü �߰� �۾��� ó�� ��,
	ProcessAddUI();

	// 2. UI ��ü �ʱ�ȭ
	for (shared_ptr<UI> ui : _uis)
		ui->BeginPlay();
}

void UIManager::Update()
{
	// 1. ��û�� UI �߰� �۾��� �����ϰ�, 
	ProcessAddUI();
	
	// 2. UI Tick ����
	for (shared_ptr<UI> ui : _uis)
	{
		if (ui->GetEnabled())
			ui->Tick();
	}

	// 3. ��û�� UI ���� �۾��� �����Ѵ�
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

			// �κ��丮 ������ 
			if (!inven->GetVisible())
			{
				// �巡�� ���� �ʱ�ȭ
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

		// ������ ����� ã��,
		auto it = find(_uis.begin(), _uis.end(), target);
		// �߰��ߴٸ�,
		if (it != _uis.end())
		{
			// ������ ����� �������� ����,
			*it = move(_uis.back());
			// ����ִ� ������ ��Ҵ� ����
			_uis.pop_back();
		}
	}
}
