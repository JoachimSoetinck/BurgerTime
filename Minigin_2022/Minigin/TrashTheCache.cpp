#include "MiniginPCH.h"
#include "TrashTheCache.h"
#include  "imgui_plot.h"

#include "imgui.h"

constexpr size_t buf_size = 512;
static float x_data[buf_size];
static float y_data1[buf_size];
static float y_data2[buf_size];


void TrashTheCache::DrawGrid() 
{

	if (ImGui::Button("Trash the cache"))
	{
		GetTimesInt();
		
	}
	if (!m_TimeIntegers.empty())
	{
			ImGui::PlotLines("Integer Times",
				m_TimeIntegers.data(),
				(int)m_TimeIntegers.size(),
				0,
				nullptr,
				0.f,
				m_TimeIntegers[0],
				ImVec2(0.f, 80.f)
			);
		
	}

}

void TrashTheCache::DrawGrid2()
{

	if (ImGui::Button("Trash the cache Game Object"))
	{
		GetTimesGameObj();
	}
	if (!m_TimeGameObjects.empty())
	{

		ImGui::PlotLines("GameObj Times",
			m_TimeGameObjects.data(),
			(int)m_TimeGameObjects.size(),
			0,
			nullptr,
			0.f,
			m_TimeGameObjects[0],
			ImVec2(0.f, 80.f)
		);

	}

	if (ImGui::Button("Trash the cache Game Object Alt"))
	{
		GetTimesGameObjAlt();
	}
	if (!m_TimeGameObjectsAlt.empty())
	{

		ImGui::PlotLines("GameObj Times",
			m_TimeGameObjectsAlt.data(),
			(int)m_TimeGameObjectsAlt.size(),
			0,
			nullptr,
			0.f,
			m_TimeGameObjectsAlt[0],
			ImVec2(0.f, 80.f)
		);

	}
}

TrashTheCache::TrashTheCache()
{

}


void TrashTheCache::GetTimesInt() 
{
	m_TimeGameObjects.clear();
	std::vector<int*> myArray;
	for (size_t i = 0; i < 1000000; i++)
	{
		myArray.push_back(new int(5));
	}

	int j = 0;
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < myArray.size(); i += stepSize)
		{
			*myArray[i] *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();

		m_TimeIntegers.push_back((float)duration);
		std::cout << stepSize << ";" << duration << std::endl;

		x_data[j] = (float)stepSize;
		

		++j;
	}


	

	for (auto i : myArray)
	{
		delete i;
		i = nullptr;
	}
	myArray.clear();
}

void TrashTheCache::GetTimesGameObj()
{


	m_TimeGameObjects.clear();
	std::vector<GameObject3D*> myArray;
	for (size_t i = 0; i < 1000000; i++)
	{
		myArray.push_back(new GameObject3D());
	}

	int j = 0;
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < myArray.size(); i += stepSize)
		{
			myArray[i]->ID *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();

		m_TimeGameObjects.push_back((float)duration);
		std::cout << stepSize << ";" << duration << std::endl;

		x_data[j] = (float)stepSize;

		++j;
	}

	for (auto i : myArray)
	{
		delete i;
		i = nullptr;
	}
	myArray.clear();
}

void TrashTheCache::GetTimesGameObjAlt()
{


	m_TimeGameObjectsAlt.clear();
	std::vector<GameObject3DAlt*> myArray;
	for (size_t i = 0; i < 1000000; i++)
	{
		myArray.push_back(new GameObject3DAlt());
	}

	int j = 0;
	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < myArray.size(); i += stepSize)
		{
			myArray[i]->ID *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count();

		m_TimeGameObjectsAlt.push_back((float)duration);
		std::cout << stepSize << ";" << duration << std::endl;

		x_data[j] = (float)stepSize;

		++j;
	}




	for (auto i : myArray)
	{
		delete i;
		i = nullptr;
	}
	myArray.clear();
}
