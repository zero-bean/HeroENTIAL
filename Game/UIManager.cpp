#include "pch.h"
#include "UIManager.h"
#include "UI.h"
#include "Panel.h"

void UIManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void UIManager::BeginPlay()
{
	while (!_addQueue.empty())
	{
		auto target = _addQueue.front();
		_addQueue.pop();

		_uis.push_back(target);
	}

	for (shared_ptr<UI> ui : _uis)
		ui->BeginPlay();
}

void UIManager::Update()
{
	while (!_removeQueue.empty())
	{
		auto target = _removeQueue.front();
		_removeQueue.pop();

		auto it = std::remove(_uis.begin(), _uis.end(), target);
		if (it != _uis.end())
			_uis.erase(it, _uis.end());
	}
	
	for (shared_ptr<UI> ui : _uis)
		ui->Tick();

	while (!_addQueue.empty())
	{
		auto target = _addQueue.front();
		_addQueue.pop();

		_uis.push_back(target);
	}
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
