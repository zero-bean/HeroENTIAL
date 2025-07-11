#include "pch.h"
#include "InventoryTooltip.h"
#include "Item.h"
#include "Flipbook.h"
#include "Texture.h"

InventoryTooltip::InventoryTooltip()
{

}

InventoryTooltip::~InventoryTooltip()
{

}

void InventoryTooltip::BeginPlay()
{

}

void InventoryTooltip::Tick()
{
	Super::Tick();
}

void InventoryTooltip::Render(HDC hdc)
{
	Super::Render(hdc);

	shared_ptr<Item> item = _owner.lock();
	if (!item) 
		return;

	const ItemContent content = item->GetItemContent();
	const shared_ptr<Flipbook> flip = item->GetFlipbook();
	const FlipbookInfo& info = flip->GetInfo();
	const Vec2Int spriteSize = info.size;
	Pos pos = GetPos();

	// ==== ��Ʈ ���� ====
	HFONT fontName = ::CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"���� ���");

	HFONT fontDesc = ::CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"���� ���");

	// ==== ���� ====
	const int padding = 12;
	const int charPerLine = 24;
	const int avgCharWidth = 8;
	const int lineHeight = 20;
	const int textAreaWidth = charPerLine * avgCharWidth;

	// ==== ���ڿ� ���� ====
	int nameLen = static_cast<int>(content.name.length());
	int descLen = static_cast<int>(content.desc.length());
	int eftLen = static_cast<int>(content.eft.length());

	int nameLines = (nameLen + charPerLine - 1) / charPerLine;
	int descLines = (descLen + charPerLine - 1) / charPerLine;
	int eftLines = (eftLen + charPerLine - 1) / charPerLine;

	// ==== �ؽ�Ʈ ���� ��� ====
	SIZE nameSize{}, descSize{}, eftSize{};
	::GetTextExtentPoint32(hdc, content.name.c_str(), content.name.size(), &nameSize);
	::GetTextExtentPoint32(hdc, content.desc.c_str(), content.desc.size(), &descSize);
	::GetTextExtentPoint32(hdc, content.eft.c_str(), content.eft.size(), &eftSize);

	int descHeight = descLines * lineHeight;
	int eftHeight = eftLines * lineHeight;

	// ==== ��ü ���� ũ�� ��� ====
	int bgWidth = max(textAreaWidth, spriteSize.x * 2) + padding * 2;
	int bgHeight =
		padding + nameSize.cy +            // �̸� ����
		padding + spriteSize.y * 2 +       // ��������Ʈ ����
		padding + descHeight +             // ���� ����
		padding + eftHeight +             // ȿ�� ����
		padding;                          // �е�

	// ==== DC ���� ���� ====
	int oldDC = ::SaveDC(hdc);
	HFONT oldFont = (HFONT)::SelectObject(hdc, fontDesc);

	// ==== ��� �׸��� ====
	Utils::DrawRoundRectColored(hdc, { pos.x, pos.y }, bgWidth, bgHeight, RGB(140, 195, 196), RGB(255, 252, 231));

	// ==== ������ �̸� ��� ====
	::SelectObject(hdc, fontName);
	::SetBkMode(hdc, TRANSPARENT);
	::SetTextColor(hdc, RGB(255, 255, 0));
	int nameX = pos.x + (bgWidth - nameSize.cx) / 2;
	::TextOut(hdc, nameX, pos.y + padding, content.name.c_str(), content.name.size());

	// ==== ������ ��������Ʈ ��� ====
	int spriteX = pos.x + (bgWidth - spriteSize.x * 2) / 2;
	int spriteY = pos.y + padding + nameSize.cy + padding;
	TransparentBlt(hdc,
		spriteX,
		spriteY,
		spriteSize.x * 2,
		spriteSize.y * 2,
		info.texture->GetDC(),
		info.start * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());

	// ==== ������ ���� ��� ====
	RECT descRect = {
		static_cast<LONG>(pos.x + padding),
		static_cast<LONG>(pos.y + padding + nameSize.cy + padding + spriteSize.y * 2),
		static_cast<LONG>(pos.x + bgWidth - padding),
		static_cast<LONG>(pos.y + padding + nameSize.cy + padding + spriteSize.y * 2 + descHeight + padding)
	};
	Utils::DrawTextMultiline(hdc, content.desc.c_str(), descRect, fontDesc, RGB(255, 255, 255));

	// ==== ������ ȿ�� ��� ====
	RECT eftRect = {
		static_cast<LONG>(pos.x + padding),
		static_cast<LONG>(descRect.bottom + padding),
		static_cast<LONG>(pos.x + bgWidth - padding),
		static_cast<LONG>(descRect.bottom + padding + eftHeight)
	};
	Utils::DrawTextMultiline(hdc, content.eft.c_str(), eftRect, fontDesc, RGB(255, 215, 0));

	// ==== ���� ====
	::SelectObject(hdc, oldFont);
	::DeleteObject(fontName);
	::DeleteObject(fontDesc);
	::RestoreDC(hdc, oldDC);
}

