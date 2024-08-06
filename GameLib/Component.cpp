#include "pch.h"
#include "Component.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CreateComponent.h"


void Component::compInit(GameObject* _gameObject, const CompIdx& idx)
{
	gameObject = _gameObject;
	compidx = idx;

	Init();
}

void Component::Init()
{
}

Component::Component()
{
	gameObject = nullptr;


}

Component::~Component()
{
}


void Component::FixedUpdate()
{
}

