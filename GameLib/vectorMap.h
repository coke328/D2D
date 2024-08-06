#pragma once
#include <vector>
#include <unordered_map>
#include <utility>
#include <type_traits>



template<typename T1, typename T2>
class vectorMap
{
	std::vector<T2> Vector;
	std::unordered_map<T1, unsigned int> Map;

public:
	vectorMap();
	~vectorMap();

	unsigned int Size();
	T2 FindObject(const T1& key);
	unsigned int FindIdx(const T1& key);
	bool isIn(const T1& key);
	bool Push(const T1& key, const T2& object);
	bool Erase(const T1& key);
	bool EraseDelete(const T1& key);
	void Clear();
	void ClearDelete();
	std::vector<T2>& operator*();

};


template<typename T1, typename T2>
inline vectorMap<T1, T2>::vectorMap()
{
	
}

template<typename T1, typename T2>
inline vectorMap<T1, T2>::~vectorMap()
{
	Clear();
}

template<typename T1, typename T2>
inline unsigned int vectorMap<T1, T2>::Size()
{
	return Vector.size();
}

template<typename T1, typename T2>
inline T2 vectorMap<T1, T2>::FindObject(const T1& key)
{
	auto it = Map.find(key);
	if (it == Map.end()) {
		//std::cout << "not found" << std::endl;
		return NULL;
	}
	else return Vector[it->second];
}

template<typename T1, typename T2>
inline unsigned int vectorMap<T1, T2>::FindIdx(const T1& key)
{
	auto result = Map.find(key);
	if (result == Map.end()) return -1;
	else return Map.at(key);
}

template<typename T1, typename T2>
inline bool vectorMap<T1, T2>::isIn(const T1& key)
{
	if (Map.count(key)) return true;
	return false;
}

template<typename T1, typename T2>
inline bool vectorMap<T1, T2>::Push(const T1& key, const T2& object)
{
	if (isIn(key)) return false;

	Map.insert({ key, Vector.size() });
	Vector.push_back(object);

	return true;
}

template<typename T1, typename T2>
inline bool vectorMap<T1, T2>::Erase(const T1& key)
{
	if (!isIn(key)) return false;

	Vector.erase(Vector.begin() + FindIdx(key));
	Map.erase(key);

	return true;
}

template<typename T1, typename T2>
inline bool vectorMap<T1, T2>::EraseDelete(const T1& key)
{
	if (!isIn(key)) return false;

	delete FindObject(key);
	Vector.erase(Vector.begin() + FindIdx(key));
	Map.erase(key);

	return true;
}

template<typename T1, typename T2>
inline void vectorMap<T1, T2>::Clear()//whether its pointer just clear
{
	Vector.clear();
	Map.clear();
}

template<typename T1, typename T2>
inline void vectorMap<T1, T2>::ClearDelete()
{
	for (auto i : Vector) {
		delete i;
	}

	Vector.clear();
	Map.clear();
}

template<typename T1, typename T2>
inline std::vector<T2>& vectorMap<T1, T2>::operator*()
{
	return Vector;
}
