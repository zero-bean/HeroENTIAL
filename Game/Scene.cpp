#include "pch.h"
#include "Scene.h"
#include "Actor.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (const shared_ptr<Actor>& actor : actors)
			actor->BeginPlay();
}

void Scene::Update()
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (const shared_ptr<Actor>& actor : actors)
			actor->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const vector<shared_ptr<Actor>>& actors : _actors)
		for (const shared_ptr<Actor>& actor : actors)
			actor->Render(hdc);
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

