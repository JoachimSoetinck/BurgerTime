#pragma once
#include <vector>
#include <chrono>
#include <string>

class TrashTheCache
{

public:
	
	TrashTheCache();

	void DrawGrid();
	void DrawGrid2();

private:

	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class GameObject3D
	{
	public:
		Transform transform{};
		int ID{ 1 };

	};

	class GameObject3DAlt
	{
	public:
		Transform* transform{};
		int ID{ 1 };

	};



	void GetTimesInt( ) ;
	void GetTimesGameObj( ) ;
	void GetTimesGameObjAlt( ) ;
	std::vector<float> m_TimeIntegers{};
	std::vector<float> m_TimeGameObjects{};
	std::vector<float> m_TimeGameObjectsAlt{};
	bool m_CanDraw;



};

