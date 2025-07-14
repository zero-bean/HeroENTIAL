#pragma once
#include "UI.h"

class Quest;
class Button;
class Font;

class QuestSlot : public UI, public enable_shared_from_this<QuestSlot>
{
	using Super = UI;
public:
    QuestSlot(shared_ptr<Quest> quest);
    virtual ~QuestSlot();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
    virtual void Render(HDC hdc) override;

private:
    shared_ptr<Quest> _quest = {};
	vector<shared_ptr<Button>> _buttons = {};
	shared_ptr<Font> _font = nullptr;
};

