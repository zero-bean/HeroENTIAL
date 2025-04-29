#include "pch.h"
#include "QuickslotPanel.h"
#include "QuickslotContainer.h"

QuickslotPanel::QuickslotPanel()
{
	// �����̳�
	_container = make_shared<QuickslotContainer>();
	AddChild(_container);

}

QuickslotPanel::~QuickslotPanel()
{
}

void QuickslotPanel::BeginPlay()
{
	Super::BeginPlay();

	// �г�
	SetSize({ 192 * 3, 192 });
	SetPos({ GWinSizeX / 2, (float)GWinSizeY });

	// �����̳�
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
