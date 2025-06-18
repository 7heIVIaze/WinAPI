#pragma once

#define SINGLE(type) public:\
						static type* GetInst() \
						{ /* 이렇게 하면, 메모리 주소를 넘겨주기 때문에 외부에서도 접근이 가능하고, 해제를 해주지 않아도 됨.*/\
							static type mgr;  \
							return &mgr; \
						}\
					private: \
						type(); \
						~type();

#define fDeltaTime CTimeManager::GetInst()->GetfDeltaTime()
#define DeltaTime CTimeManager::GetInst()->GetDeltaTime()

#define KEY_CHECK(key, state) CKeyManager::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)



enum class GROUP_TYPE
{
	DEFAULT,	// 0
	PLAYER,		// 1
	MISSILE,	// 2
	MONSTER,	// 3

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};