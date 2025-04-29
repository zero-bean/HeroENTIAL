#include "pch.h"
#include "QuickslotPanel.h"
#include "QuickslotContainer.h"

QuickslotPanel::QuickslotPanel()
{
	// 컨테이너
	_container = make_shared<QuickslotContainer>();
	AddChild(_container);

}

QuickslotPanel::~QuickslotPanel()
{
}

void QuickslotPanel::BeginPlay()
{
	Super::BeginPlay();

	// 패널
	SetSize({ 192 * 3, 192 });
	SetPos({ GWinSizeX / 2, (float)GWinSizeY });

	// 컨테이너
	_container->SetPos(GetPos());
}

void QuickslotPanel::Tick()
{
	Super::Tick();

}

void QuickslotPanel::Render(HDC hdc)
{
	Super::Render(hdc);


}
