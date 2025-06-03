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
	for (shared_ptr<UI> ui : _uis)
		ui->BeginPlay();
}

void UIManager::Update()
{
	for (shared_ptr<UI> ui : _uis)
		ui->Tick();
}

void UIManager::Render(HDC hdc)
{
	for (shared_ptr<UI> ui : _uis)
		ui->Render(hdc);
}

void UIManager::Clear()
{
	_uis.clear();
	_drag = {};
}

void UIManager::AddUI(shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_uis.push_back(ui);
}

void UIManager::RemoveUI(shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	vector<shared_ptr<UI>>& v = _uis;
	v.erase(std::remove(v.begin(), v.end(), ui), v.end());
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
