#pragma once

#include "Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent() override;

public:
	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

};

