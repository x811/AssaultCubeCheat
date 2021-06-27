#pragma once
#include <Windows.h>
#include <cstdint>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class Vector2
{
public:
	float x, y;
};

class Vector3 {
public:
	//constructors
	constexpr Vector3(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}
	constexpr Vector3(float ia) : x(ia), y(ia), z(ia) {}
	constexpr Vector3() : x(0), y(0), z(0) {}

	//variables
	float x, y, z;

	//operators
	Vector3 operator+(const Vector3& right) const;
	Vector3 operator-(const Vector3& right) const;
	Vector3 operator-() const { return Vector3(-x, -y, -z); };
	Vector3 operator*(const Vector3& right) const;
	Vector3 operator/(const Vector3& right) const;
	Vector3& operator+=(const Vector3& right);
	Vector3& operator-=(const Vector3& right);
	Vector3& operator*=(const Vector3& right);
	Vector3& operator/=(const Vector3& right);

};

class CWeapon
{

};

class CPlayer
{
public:
	uintptr_t vTable; //0x0000
	Vector3 m_vecHeadPos; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 m_vecPos; //0x0034
	Vector3 m_vecViewAngles; //0x0040
	char pad_004C[34]; //0x004C
	bool bCrouching; //0x006E
	char pad_006F[137]; //0x006F
	int32_t m_iHealth; //0x00F8
	int32_t m_iArmor; //0x00FC
	char pad_0100[292]; //0x0100
	bool bAttacking; //0x0224
	char m_sName[16]; //0x0225
	char pad_0235[247]; //0x0235
	uint8_t m_iTeamNum; //0x032C
	char pad_032D[11]; //0x032D
	uint8_t m_uState; //0x0338
	char pad_0339[59]; //0x0339
	class CurrentWeapon* m_iCurrWeapon; //0x0374
	char pad_0378[282]; //0x0378
}; 

class EntityList
{
public:
	CPlayer* pPlayerArray[32];
};