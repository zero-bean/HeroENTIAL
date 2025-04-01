#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Creature.h"
#include "UI.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->BeginPlay();

	for (shared_ptr<UI> ui : _uis)
		ui->BeginPlay();
}

void Scene::Update()
{
	for (const vector<shared_ptr<Actor>> actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->Tick();

	for (shared_ptr<UI> ui : _uis)
		ui->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (shared_ptr<Actor> actor : actors)
			actor->Render(hdc);

	for (shared_ptr<UI> ui : _uis)
		ui->Render(hdc);
}

void Scene::AddActor(shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;
	
	vector<shared_ptr<Actor>>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

void Scene::AddUI(shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_uis.push_back(ui);
}

void Scene::RemoveUI(shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	vector<shared_ptr<UI>>& v = _uis;
	v.erase(std::remove(v.begin(), v.end(), ui), v.end());
}

shared_ptr<Creature> Scene::GetCreatureAt(Vec2Int cellPos)
{
	for (const shared_ptr<Actor>& actor : _actors[LAYER_OBJECT])
	{
		// GameObjectType
		shared_ptr<Creature> creature = dynamic_pointer_cast<Creature>(actor);
		if (creature && (Vec2Int)creature->GetCellPos() == cellPos)
			return creature;
	}

	return nullptr;
}

