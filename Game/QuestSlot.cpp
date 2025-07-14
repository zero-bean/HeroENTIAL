#include "pch.h"
#include "Quest.h"
#include "QuestSlot.h"
#include "Button.h"
#include "Font.h"

QuestSlot::QuestSlot(std::shared_ptr<Quest> quest) : _quest(quest)
{
    SetSize({ 500, 100 }); // 슬롯 사이즈 고정

    // font
	_font = ResourceManager::GET_SINGLE()->GetFont(L"DungeonFont32");

    // button
    _buttons.resize(2);

    _buttons[0] = make_shared<Button>();
	_buttons[0]->SetSize({ 64, 64 });
    _buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Accept"), BS_Default);
    _buttons[0]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Accept_Pressed"), BS_Pressed);

    _buttons[1] = make_shared<Button>();
	_buttons[1]->SetSize({ 64, 64 });
    _buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Cancle"), BS_Default);
    _buttons[1]->SetSprite(ResourceManager::GET_SINGLE()->GetSprite(L"Button_Cancle_Pressed"), BS_Pressed);
}

QuestSlot::~QuestSlot() 
{
    _quest = nullptr;
    _buttons.clear();
    _font = nullptr;
}

void QuestSlot::BeginPlay()
{
    auto self = shared_from_this();

    const Vec2Int slotSize = GetSize();
    const Vec2 slotPos = GetPos();
    const float buttonSpacing = 10.0f;

    // 버튼
    Vec2 btn1Pos = {
        slotPos.x + slotSize.x / 2 - _buttons[1]->GetSize().x - buttonSpacing,
        slotPos.y
    };
    Vec2 btn2Pos = {
        btn1Pos.x - _buttons[0]->GetSize().x - buttonSpacing,
        slotPos.y
    };

    _buttons[1]->SetPos(btn1Pos);
    _buttons[0]->SetPos(btn2Pos);

    // 클릭 이벤트
    _buttons[0]->AddOnClickDelegate(self, [this]() {
        SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
        if (_quest->GetState() == ProgressState::Inactive)
        {
            _quest->SetActive();
            _buttons[0]->SetEnabled(false);
            _buttons[0]->SetVisible(false);
            _buttons[1]->SetEnabled(true);
            _buttons[1]->SetVisible(true);
        }
        else if (_quest->GetState() == ProgressState::Completed)
        {
			SoundManager::GET_SINGLE()->Play(L"SFX_QUESTCLEAR");
            _buttons[0]->SetEnabled(false);
            _buttons[0]->SetVisible(false);
            _buttons[1]->SetEnabled(false);
            _buttons[1]->SetVisible(false);
            _quest->SetFinished();
        }
        });

    _buttons[1]->AddOnClickDelegate(self, [this]() {
        SoundManager::GET_SINGLE()->Play(L"SFX_CLICK");
        if (_quest->GetState() == ProgressState::Active
            || _quest->GetState() == ProgressState::Completed)
        {
            _quest->ResetProgress();
            _buttons[0]->SetEnabled(true);
            _buttons[0]->SetVisible(true);
            _buttons[1]->SetEnabled(false);
            _buttons[1]->SetVisible(false);
        }
        });

    // 상태에 따라 버튼 비활성화
    ProgressState state = _quest->GetState();
    if (state == ProgressState::Active)
    {
        _buttons[0]->SetEnabled(false); 
		_buttons[0]->SetVisible(false); 
        _buttons[1]->SetEnabled(true);   
		_buttons[1]->SetVisible(true);
    }
    else if (state == ProgressState::Completed)
    {
        _buttons[0]->SetEnabled(true); 
		_buttons[0]->SetVisible(true); 
        _buttons[1]->SetEnabled(true);
		_buttons[1]->SetVisible(true);
    }
	else if (state == ProgressState::Inactive)
    {
        _buttons[0]->SetEnabled(true);
		_buttons[0]->SetVisible(true);
        _buttons[1]->SetEnabled(false); 
		_buttons[1]->SetVisible(false); 
    }
    else if (state == ProgressState::Finished)
    {
        _buttons[0]->SetEnabled(false);
        _buttons[0]->SetVisible(false);
        _buttons[1]->SetEnabled(false);
        _buttons[1]->SetVisible(false);
    }

    Super::BeginPlay();
}


void QuestSlot::Tick()
{
	Super::Tick();

    if (_buttons[0]->GetEnabled())
	    _buttons[0]->Tick();
	
	if (_buttons[1]->GetEnabled())
        _buttons[1]->Tick();
}

void QuestSlot::Render(HDC hdc)
{
    Super::Render(hdc);

    // 텍스트 출력 위치: 왼쪽 정렬
    float textMarginX = -GetSize().x / 2 + 10;
    float textStartX = _pos.x + textMarginX;
    float textY = _pos.y - 20;

    Utils::DrawTextColored(hdc, { textStartX, textY }, _quest->GetName(), _font->GetHandle(), RGB(255, 255, 0));
    textY += 25;
    Utils::DrawTextColored(hdc, { textStartX, textY }, _quest->GetDescription(), _font->GetHandle(), RGB(255, 155, 0));

    // 버튼
	if (_buttons[0]->GetVisible())
        _buttons[0]->Render(hdc);
	if (_buttons[1]->GetVisible())
        _buttons[1]->Render(hdc);
}
