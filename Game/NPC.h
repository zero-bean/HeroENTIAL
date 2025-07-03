#pragma once
#include "Creature.h"

class Flipbook;
class Collider;
class Font;

class NPC : public Creature
{
	using Super = Creature;
public:
	NPC();
	virtual ~NPC();

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	virtual void OnComponentBeginOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;
	virtual void OnComponentEndOverlap(shared_ptr<Collider> collider, shared_ptr<Collider> other) override;

	virtual void AddCollider(const Vec2 size) override;

	// 현재는 로비 NPC만 사용하니 비활성화 .. 나중에 하위 NPC 클래스가 나뉘어지면 옮길듯
	virtual void OnDamaged(shared_ptr<Creature> attacker) override {}
	virtual void OnDamaged(shared_ptr<Projectile> projectile) override {}

public:
	void SetOnActivate(function<void()> active) { _onActivate = active; }
	void SetOnDeActivate(function<void()> dective) { _onDeactivate = dective; }

public:
	void SetRoleText(const wstring& text) { _roleText = text; }

private:
	virtual void TickIdle() override {}
	virtual void TickMove() override {}
	virtual void TickAttack() override {}
	virtual void TickAttacked() override {}
	virtual void TickDeath() override {}
	virtual void TickBirth() override {}

	virtual void UpdateAnimation() override;

private:
	bool isPlayerOverlapped = false;
	function<void()> _onActivate = {};
	function<void()> _onDeactivate = {};

	shared_ptr<Font> _font = nullptr;
	wstring _roleText = {};
	wstring _interactText = L"[Press z]";

private:
	shared_ptr<Flipbook> _idle[2] = {};
	shared_ptr<Flipbook> _move[2] = {};
	shared_ptr<Flipbook> _axing[2] = {};
	shared_ptr<Flipbook> _hammering[2] = {};
	shared_ptr<Flipbook> _idle_Holding[2] = {};
	shared_ptr<Flipbook> _move_Holding[2] = {};
};

