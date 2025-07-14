#pragma once

/* 02. Scene */
enum class SceneType
{
	None,
	DevScene,
	LobbyScene,
	BattleScene,
	Stage1,
	Stage2,
};

enum class ScenePhase
{
	None,
	Normal,
	BossIntroStart,
	BossIntroEnd,
	StageClear,
};

enum LAYER_TYPE
{
	LAYER_CAMERA,
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_EFFECT,
	LAYER_UI,
	LAYER_MAXCOUNT
};

/* 03. Object */
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
	Stunned,
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

enum class ShakeType
{
	Explosion,  // 폭발
	Earthquake, // 지진
	HitRecoil,  // 피격
	SubtlePulse // 보스 구르기 패턴..?
};

enum class Rank
{
	Common,
	Rare,
	Elite,
	Boss,
};

/* 04. Resources */
enum class TILE_TYPE
{
	EMPTY,
	WALL,
	OBJECT,
	PLAYER,
	MONSTER,
	PROJECTILE,
	NPC,
	ITEM,
};

/* 05. Component */
enum COLLISION_LAYER_TYPE : unsigned __int8
{
	CLT_BULLET,
	CLT_MYBULLET,
	CLT_PLAYER,
	CLT_NPC,
	CLT_MONSTER,
	CLT_OBJECT,
	CLT_LAYER,
	CLT_GROUND,
	CLT_WALL,
	// ...
};

/* 07. Systems */
enum class ProgressType {
	Quest,
	Achievement
};

enum class ProgressState {
	Inactive,
	Active,
	Completed,
	Finished
};

enum class EventType {
	MonsterKilled,
	StageCleared,
	ItemAcquired
};

enum class QuestConditionType {
	KillMonster,
	DungeonClearWithHp
};
