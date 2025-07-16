#pragma once

class Quest;

class QuestSystem
{
public:
	QuestSystem() {}
	~QuestSystem() {}

public:
	void Init();

public:
	void Notify(EventType type, const wstring& param);
	const vector<shared_ptr<Quest>>& GetAllQuests() const;

private:
	vector<shared_ptr<Quest>> _questList = {};
};

