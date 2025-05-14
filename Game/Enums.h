#pragma once

enum class SceneType
{
	None,
	DevScene,
	LobbyScene,
	EditScene,
	BasicScene,
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_EFFECT,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum COLLISION_LAYER_TYPE : unsigned __int8
{
	CLT_PLAYER,
	CLT_NPC,
	CLT_MONSTER,
	CLT_OBJECT,
	CLT_BULLET,
	CLT_GROUND,
	CLT_WALL,
	// ...
};

enum Dir
{
	DIR_RIGHT,
	DIR_LEFT,
	DIR_UP,
	DIR_DOWN,
};

enum class ObjectState
{
	Idle,
	Move,
	Attack,
	Attacked,
	Skill,
	Death,
	Birth,
};

enum class WeaponType
{
	Sword,
	Bow,
	Staff
};

enum class ItemType
{
	Equipment,
	Consumable,
	Others,
	Quick,
	MAX_COUNT
};