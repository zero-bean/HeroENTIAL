#pragma once

class Actor;
class Creature;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

public:
	virtual void AddActor(shared_ptr<Actor> actor);
	virtual void RemoveActor(shared_ptr<Actor> actor);
	
	shared_ptr<Creature> GetCreatureAt(Vec2Int cellPos);

protected:
	vector<shared_ptr<Actor>> _actors[LAYER_MAXCOUNT];

};

