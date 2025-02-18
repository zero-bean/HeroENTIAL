#pragma once

class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

public:
	virtual void LoadFile(const wstring& path);
	virtual void SaveFile(const wstring& path);
};

