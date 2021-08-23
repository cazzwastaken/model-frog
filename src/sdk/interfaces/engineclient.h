#pragma once
#include "netchannel.h"

class EngineClient
{
public:
	NetChannelInfo* GetNetChannelInfo()
	{
		return m::Call<NetChannelInfo*>(this, 78);
	}
};
