#include "pch.h"
#include "HPbar.h"
#include "Creature.h"
#include "SceneManager.h"

void HPbar::BeginPlay()
{

}

void HPbar::Tick()
{
    if (auto owner = _owner.lock())
        SetPos(owner->GetPos());
}

void HPbar::Render(HDC hdc)
{
    if (auto owner = _owner.lock())
    {
        Stat& stat = owner->GetStat();
        float ratio = (float)stat.hp / stat.maxHp;
        if (ratio >= 1.f)
            return;
        Vec2Int size = { 60, 8 };
        Vec2 camera = SceneManager::GET_SINGLE()->GetCameraPos();
        Vec2 renderPos = GetPos() - Vec2(size.x / 2, size.y / 2) - camera + Vec2(GWinSizeX / 2, GWinSizeY / 2) + Vec2(0, 80);

        // 배경
        Utils::DrawRectColored(hdc, renderPos, size.x, size.y, RGB(80, 80, 80), RGB(0, 0, 0));
        // HP 게이지
        Utils::DrawRectColored(hdc, renderPos, size.x * ratio, size.y, RGB(255, 50, 50), RGB(255, 50, 50));
    }
}
