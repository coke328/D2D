#include "pch.h"
#include "CreateComponent.h"

Components::Components()
{
}

void Components::Sort()
{
	std::sort(Bases.begin(), Bases.end(), [](Base* b1,Base* b2) {
		return b1->sortOrder < b2->sortOrder;
		});

	for (unsigned int i = 0; i < Bases.size(); i++) {
		Bases[i]->compsIdx = i;
	}
}

void* Components::GetComponent(const CompIdx& idx)
{
	return Bases[*idx.first]->get(*idx.second);
}

void Components::EraseComponent(const CompIdx& idx)
{
	Bases[*idx.first]->Erase(*idx.second);
}

unsigned int Components::GetCapacity(unsigned int i)
{
	return Bases[i]->vecCap;
}

Components& Components::GetInstance()
{
	static Components t;
	return t;
}

void Components::ComponentsUpdate()
{
	unsigned int minus = 0;
	for (auto i = Bases.begin(); i != Bases.end(); ++i) {
		if (*i == nullptr) {
			minus++;
			i = Bases.erase(i);
		}
		(*i)->compsIdx -= minus;
		(*i)->Update();
	}
}


Base::Base() {
	sortOrder = 0;

}

voidPComponent::voidPComponent(const CompIdx& _idx)
{
	idx = _idx;
	tmpPtr = Components::GetInstance().GetComponent(idx);
	vecCap = Components::GetInstance().GetCapacity(*idx.first);
}

voidPComponent::voidPComponent(unsigned int _vecCap, void* p, const CompIdx& _idx)
{
	vecCap = _vecCap;
	tmpPtr = p;
	idx = _idx;
}

voidPComponent& voidPComponent::operator=(const CompIdx& _idx)
{
	idx = _idx;
	tmpPtr = Components::GetInstance().GetComponent(idx);
	vecCap = Components::GetInstance().GetCapacity(*idx.first);
	return *this;
}
