#include "pch.h"
#include "DungeonEnterPanel.h"
#include "DungeonEnterContainer.h"
#include "Button.h"
#include "Font.h"

DungeonEnterPanel::DungeonEnterPanel()
{
	// �г�
	SetPos({ GWinSizeX / 2, GWinSizeY / 3 });
	SetSize({ 1500, 600 });

	// �����̳�
	_container = make_shared<DungeonEnterContainer>();
	_container->SetPos(GetPos());
	AddChild(_container);

	// ��ư
	_buttons.resize(6, nullptr);

	_buttons[0] = make_shared<Button>();
	_buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage1_Regular"), BS_Default);
	_buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage1_Pressed"), BS_Pressed);
	AddChild(_buttons[0]);

	_buttons[1] = make_shared<Button>();
	_buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage2_Regular"), BS_Default);
	_buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage2_Pressed"), BS_Pressed);
	AddChild(_buttons[1]);

	_buttons[2] = make_shared<Button>();
	_buttons[2]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage3_Regular"), BS_Default);
	_buttons[2]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage3_Pressed"), BS_Pressed);
	AddChild(_buttons[2]);

	_buttons[3] = make_shared<Button>();
	_buttons[3]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage4_Regular"), BS_Default);
	_buttons[3]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage4_Pressed"), BS_Pressed);
	AddChild(_buttons[3]);

	_buttons[4] = make_shared<Button>();
	_buttons[4]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage5_Regular"), BS_Default);
	_buttons[4]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage5_Pressed"), BS_Pressed);
	AddChild(_buttons[4]);

	_buttons[5] = make_shared<Button>();
	_buttons[5]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage6_Regular"), BS_Default);
	_buttons[5]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Stage6_Pressed"), BS_Pressed);
	AddChild(_buttons[5]);

	// ��Ʈ
	_font = ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont64");
}

DungeonEnterPanel::~DungeonEnterPanel()
{
}

void DungeonEnterPanel::BeginPlay()
{
	float startX = GetPos().x - 300; /* 120 x 5 % 2 */
	float btnY = GetPos().y / 2;
	auto self = shared_from_this(); // self�� ������� ������, Scene ������ �� �Ҹ�� ������ ������ ũ���� �߻�
	for (int i = 0; i < _buttons.size(); i++)
	{
		int stageIdx = i;
		_buttons[i]->SetSize({ 100, 100 });
		_buttons[i]->SetPos({ startX + (120 * i), btnY + _buttons[i]->GetSize().y + 50 });
		_buttons[i]->AddOnClickDelegate([self, stageIdx]() {
			self->SetButtonFunction(stageIdx);
			});
	}

	Super::BeginPlay();
}

void DungeonEnterPanel::Tick()
{
	Super::Tick();
}

void DungeonEnterPanel::Render(HDC hdc)
{
	Super::Render(hdc);

	// ��Ʈ
	if (_font)
	{
		const wstring str = L"Choose the Stage !";
		const HFONT font = _font->GetHandle();
		const int fontSize = _font->GetSize();
		Utils::DrawTextColored(hdc, 
			{ GetPos().x / 2 + fontSize * 2, GetPos().y / 4 + fontSize }, 
			str, font, RGB(0, 0, 0));
	}
}

void DungeonEnterPanel::SetButtonFunction(const int idx)
{
	// ���� ���
	SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");

	switch (idx)
	{
	case 0:
		SceneManager::GET_SINGLE()->RequestToChangeScene(SceneType::Stage1);
		break;
	case 1:
		SceneManager::GET_SINGLE()->RequestToChangeScene(SceneType::Stage2);
		break;
	default:
		return;
	}

	UIManager::GET_SINGLE()->RemoveUI(shared_from_this());
}
