#pragma once

namespace GameEngine
{

public interface class IUpdatable
{
public:
	void Update(float timeTotal, float timeDelta);
};

}