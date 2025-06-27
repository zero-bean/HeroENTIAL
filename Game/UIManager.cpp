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
		ui->Tick();

	// 3. 요청된 UI 삭제 작업을 진행한다
	ProcessRemoveUI();
}

void UIManager::Render(HDC hdc)
{
	for (shared_ptr<UI> ui : _uis)
		ui->Render(hdc);
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
			// 맨 뒤로 보내어 제거 : O(1), 정렬X면 가능
			iter_swap(it, prev(_uis.end()));
			_uis.pop_back();
		}
	}
}
