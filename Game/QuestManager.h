#pragma once

class Quest;

class QuestManager
{
public:
	static QuestManager* GET_SINGLE()
	{
		static QuestManager instance;
		return &instance;
	}

private:
	QuestManager() {}
	~QuestManager() {}

	QuestManager(const QuestManager&) = delete;
	QuestManager operator=(const QuestManager&) = delete;

public:
	void Init();

public:
	void Notify(EventType type, const wstring& param);
	const vector<shared_ptr<Quest>>& GetAllQuests() const;

private:
	vector<shared_ptr<Quest>> _questList = {};
};

