#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class Task2 : public QuestTask
{
public:
	static Task2* create(GameObject* owner, std::string questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	Task2(GameObject* owner, std::string questLine, std::string questTag);
	~Task2();
	
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;
	void enable(bool isSkippable) override;
	void disable() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};
