#pragma once

typedef std::pair<unsigned int*, unsigned int*> CompIdx;

class Base;

template<typename T>
class CreateComponent;

class Physics;

class voidPComponent {
	unsigned int vecCap;
	void* tmpPtr;
	
public:
	CompIdx idx;

	template<typename T>
	T* Get();
	voidPComponent(const CompIdx& idx);
	voidPComponent(unsigned int _vecCap, void* p, const CompIdx& _idx);
	voidPComponent& operator=(const CompIdx& idx);
};

template<typename T, typename Enable = std::enable_if_t<std::is_pointer<T>::value>>
class pComponent {
	unsigned int vecCapacity;
	CompIdx idx;
public:

	T tmpPtr;

	T Get();
	pComponent();
	pComponent(unsigned int* i, unsigned int* j, unsigned int cap, T _ptr);
	pComponent(const pComponent<T>& other);
	pComponent(const CompIdx& idx);
	pComponent& operator=(const pComponent& other);
	pComponent& operator=(const CompIdx& idx);

	operator voidPComponent();

	const CompIdx& Idx();
};

enum ComponentsOrder {
	collider = 2,
	renderer = 3
};

class Components {
	template<typename T>
	friend class CreateComponent;

	std::vector<Base*> Bases;

	Components();
	
	
public:
	void Sort();
	void* GetComponent(const CompIdx& idx);
	void EraseComponent(const CompIdx& idx);
	
	unsigned int GetCapacity(unsigned int i);

	static Components& GetInstance();

	void ComponentsUpdate();
};

class Base {
	friend class Components;
protected:
	unsigned int compsIdx;
	unsigned int vecCap;
	unsigned int sortOrder;
public:
	
	virtual void Update() = 0;
	Base();
	virtual ~Base() = default;
	virtual void Erase(unsigned int j) = 0;
	virtual void* get(unsigned int j) = 0;
};





class GameObject;

template<typename T>
class CreateComponent : public Base
{
	template<typename T, typename Enable>
	friend class pComponent;

	friend class GameObject;
	
private:
	CreateComponent();
	~CreateComponent();

	std::vector<T> vector;
public:
	
	static CreateComponent& Get();
	//static void Destroy();
	std::vector<T>& Vector();
	pComponent<T*> Create();
	void Clear();
	void* get(unsigned int j) override;
	void Erase(unsigned int idx) override;
	void Update() override;
};


class RenderComponent;
class Collider;

template<typename T>
inline CreateComponent<T>::CreateComponent()
{
	if (std::is_base_of<RenderComponent, T>::value) {
		sortOrder = ComponentsOrder::renderer;
	}
	else if (std::is_base_of<Collider, T>::value) {
		sortOrder = ComponentsOrder::collider;
	}

	compsIdx = Components::GetInstance().Bases.size();
	Components::GetInstance().Bases.push_back(dynamic_cast<Base*>(this));
	Components::GetInstance().Sort();
}

template<typename T>
inline CreateComponent<T>::~CreateComponent()
{
}

template<typename T>
inline CreateComponent<T>& CreateComponent<T>::Get()
{
	static CreateComponent<T> instance;
	return instance;
}

//template<typename T>
//static void CreateComponent<T>::Destroy()
//{
//
//}

template<typename T>
inline std::vector<T>& CreateComponent<T>::Vector()
{
	return vector;
}

template<typename T>
inline void CreateComponent<T>::Erase(unsigned int _idx)
{
	vector[_idx].dest();
	vector.erase(vector.begin() + _idx);
	for (unsigned int i = _idx; i < vector.size(); i++) {
		vector[i].idx--;
	}
}

template<typename T>
inline void CreateComponent<T>::Clear()
{
	vector.clear();
}

template<typename T>
inline void* CreateComponent<T>::get(unsigned int j)
{
	return &vector[j];
}

template<typename T>
inline void CreateComponent<T>::Update()
{
	for (T& i : vector) {
		i.Update();
	}
}

template<typename T>
inline pComponent<T*> CreateComponent<T>::Create()
{
	unsigned int* _idx = new unsigned int(vector.size());
	vector.emplace_back();
	vecCap = vector.capacity();
	vector.back().idx = _idx;
	return pComponent<T*>(&compsIdx, _idx, vector.capacity(), &vector.back());
}

template<typename T, typename Enable>
inline T pComponent<T, Enable>::Get()
{
	unsigned int tmp = Components::GetInstance().GetCapacity(*idx.first);
	if (vecCapacity != tmp) {
		tmpPtr = static_cast<T>(Components::GetInstance().GetComponent(idx));
		vecCapacity = tmp;
	}
	return tmpPtr;
}

template<typename T, typename Enable>
pComponent<T, Enable>::pComponent()
{
	idx.first = nullptr;
	idx.second = 0;
	vecCapacity = 0;
	tmpPtr = nullptr;
}

template<typename T, typename Enable>
inline pComponent<T, Enable>::pComponent(unsigned int* i, unsigned int* j, unsigned int cap, T _ptr)
{
	idx.first = i;
	idx.second = j;
	vecCapacity = cap;
	tmpPtr = _ptr;
}

template<typename T, typename Enable>
pComponent<T, Enable>::pComponent(const pComponent<T>& other)
{
	idx = other.idx;
	vecCapacity = other.vecCapacity;
	tmpPtr = other.tmpPtr;
}

template<typename T, typename Enable>
pComponent<T, Enable>::pComponent(const CompIdx& _idx)
{
	idx = _idx;
}

template<typename T, typename Enable>
pComponent<T, Enable>& pComponent<T, Enable>::operator=(const pComponent<T, Enable>& other)
{
	idx = other.idx;
	vecCapacity = other.vecCapacity;
	tmpPtr = other.tmpPtr;
	return *this;
}

template<typename T, typename Enable>
pComponent<T, Enable>& pComponent<T, Enable>::operator=(const CompIdx& _idx)
{
	idx = _idx;
	return *this;
}

template<typename T, typename Enable>
inline pComponent<T, Enable>::operator voidPComponent()
{
	return { vecCapacity,tmpPtr,idx };
}

template<typename T, typename Enable>
const CompIdx& pComponent<T, Enable>::Idx()
{
	return idx;
}

template<typename T>
inline T* voidPComponent::Get()
{
	unsigned int cap = Components::GetInstance().GetCapacity(*idx.first);
	if(cap != vecCap){
		tmpPtr = Components::GetInstance().GetComponent(idx);
		vecCap = cap;
	}
	return static_cast<T*>(tmpPtr);
}
