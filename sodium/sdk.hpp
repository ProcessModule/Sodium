#pragma once

#include <thread>
#include <unordered_map>
#include <string>

#include <d3d9.h>
#include <vector>

#include "settings.hpp"
#include "driver.hpp"
#include "offsets.hpp"
#include "ida.hpp"

#define M_PI 3.14159265358979323846f

class Vector2 {
	public:
		Vector2() : x(0.f), y(0.f) {}
		Vector2(double _x, double _y) : x(_x), y(_y) {}
		~Vector2() {}

		double x, y;
};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	double x;
	double y;
	double z;

	inline double dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline bool isValid() const {
		return isfinite(x) && isfinite(y) && isfinite(z);
	}

	inline double distance(Vector3 v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double length() {
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 operator+(const Vector3& other) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
	Vector3 operator-(const Vector3& other) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
	Vector3 operator*(float offset) const { return { this->x * offset, this->y * offset, this->z * offset }; }
	Vector3 operator/(float offset) const { return { this->x / offset, this->y / offset, this->z / offset }; } // MSCV linker is actually retarded LLVM on top

	Vector3& operator*=(const double other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
	Vector3& operator/=(const double other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

	Vector3& operator=(const Vector3& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
	Vector3& operator+=(const Vector3& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	Vector3& operator-=(const Vector3& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	Vector3& operator*=(const Vector3& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
	//Vector3& operator/=(const Vector3& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

	operator bool() { return bool(this->x || this->y || this->z); }
	friend bool operator==(const Vector3& a, const Vector3& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
	//friend bool operator!=(const Vector3& a, const Vector3& b) { return !(a == b); }
};

struct FQuat { 
	double x, y, z, w; 
};

struct FTransform
{
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];

	D3DMATRIX to_matrix_with_scale() const
	{
		D3DMATRIX m{};

		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;
		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;

		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

template <typename T>
struct FArray {
	uintptr_t array = 0;
	uint32_t count = 0;
	uint32_t max_count = 0;

	uintptr_t get(uint32_t Index) const {
		if (Index >= count) {
			return 0;
		}
		return read<uintptr_t>(array + (Index * sizeof(T))); // Use sizeof(T)
	}

	uint32_t size() const {
		return count;
	}

	uintptr_t operator[](uint32_t Index) const {
		return get(Index);
	}

	bool is_valid() const {
		return array && count <= max_count && max_count <= 1000000;
	}

	uintptr_t get_address() const {
		return array;
	}
};


D3DMATRIX matrix_multiplication(const D3DMATRIX& pm1, const D3DMATRIX& pm2)
{
	D3DMATRIX pout{};

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			pout.m[row][col] = pm1.m[row][0] * pm2.m[0][col] +
				pm1.m[row][1] * pm2.m[1][col] +
				pm1.m[row][2] * pm2.m[2][col] +
				pm1.m[row][3] * pm2.m[3][col];
		}
	}

	return pout;
}

D3DMATRIX to_matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radpitch = (rot.x * M_PI / 180);
	float radyaw = (rot.y * M_PI / 180);
	float radroll = (rot.z * M_PI / 180);
	float sp = sinf(radpitch);
	float cp = cosf(radpitch);
	float sy = sinf(radyaw);
	float cy = cosf(radyaw);
	float sr = sinf(radroll);
	float cr = cosf(radroll);
	D3DMATRIX matrix{};
	matrix.m[0][0] = cp * cy;
	matrix.m[0][1] = cp * sy;
	matrix.m[0][2] = sp;
	matrix.m[0][3] = 0.f;
	matrix.m[1][0] = sr * sp * cy - cr * sy;
	matrix.m[1][1] = sr * sp * sy + cr * cy;
	matrix.m[1][2] = -sr * cp;
	matrix.m[1][3] = 0.f;
	matrix.m[2][0] = -(cr * sp * cy + sr * sy);
	matrix.m[2][1] = cy * sr - cr * sp * sy;
	matrix.m[2][2] = cr * cp;
	matrix.m[2][3] = 0.f;
	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;
	return matrix;
}

struct camera {
	Vector3 location;
	Vector3 rotation;
	float fov;
};

namespace cache {
	inline uintptr_t uworld;
	inline uintptr_t game_instance;
	inline uintptr_t local_players;
	inline uintptr_t player_controller;
	inline uintptr_t local_pawn;
	inline uintptr_t root_component;
	inline uintptr_t player_state;
	inline uintptr_t game_state;
	inline uintptr_t player_array;
	inline uintptr_t closest_pawn;
	inline uintptr_t current_weapon;

	inline int my_team_id;
	inline int player_count;

	inline float closest_distance;

	inline Vector3 relative_location;

	inline camera local_camera;
}

struct FPlane : Vector3
{
	double W;

	FPlane() : W(0) { }
	FPlane(double W) : W(W) { }
};

class FMatrix
{
public:
	double m[4][4];
	FPlane XPlane, YPlane, ZPlane, WPlane;

	FMatrix() : XPlane(), YPlane(), ZPlane(), WPlane() { }
	FMatrix(FPlane XPlane, FPlane YPlane, FPlane ZPlane, FPlane WPlane)
		: XPlane(XPlane), YPlane(YPlane), ZPlane(ZPlane), WPlane(WPlane) { }
};

inline double RadiansToDegrees(double dRadians)
{
	return dRadians * (180.0 / M_PI);
}

template< typename t >
class TArray
{
public:

	TArray() : tData(), iCount(), iMaxCount() { }
	TArray(t* data, int count, int max_count) :
		tData(tData), iCount(iCount), iMaxCount(iMaxCount) { }

public:

	auto Get(int idx) -> t
	{
		return read< t >(reinterpret_cast<__int64>(this->tData) + (idx * sizeof(t)));
	}

	auto Size() -> std::uint32_t
	{
		return this->iCount;
	}

	bool IsValid()
	{
		return this->iCount != 0;
	}

	t* tData;
	int iCount;
	int iMaxCount;
};

uintptr_t GetViewState()
{
	TArray<uintptr_t> ViewState = read<TArray<uintptr_t>>(cache::local_players + 0xD0);
	return ViewState.Get(1);
}

camera get_view_point()
{
	auto mProjection = read<FMatrix>(GetViewState() + 0x900);
	cache::local_camera.rotation.x = RadiansToDegrees(std::asin(mProjection.ZPlane.W));
	cache::local_camera.rotation.y = RadiansToDegrees(std::atan2(mProjection.YPlane.W, mProjection.XPlane.W));
	cache::local_camera.rotation.z = 0.0;

	cache::local_camera.location.x = mProjection.m[3][0];
	cache::local_camera.location.y = mProjection.m[3][1];
	cache::local_camera.location.z = mProjection.m[3][2];
	float FieldOfView = atanf(1 / read<double>(GetViewState() + 0x700)) * 2;
	cache::local_camera.fov = (FieldOfView) * (180.f / M_PI); return cache::local_camera;
}

Vector2 project_world_to_screen(Vector3 world_location)
{
	cache::local_camera = get_view_point();
	D3DMATRIX temp_matrix = to_matrix(cache::local_camera.rotation);

	Vector3 vaxisx = Vector3(temp_matrix.m[0][0], temp_matrix.m[0][1], temp_matrix.m[0][2]);
	Vector3 vaxisy = Vector3(temp_matrix.m[1][0], temp_matrix.m[1][1], temp_matrix.m[1][2]);
	Vector3 vaxisz = Vector3(temp_matrix.m[2][0], temp_matrix.m[2][1], temp_matrix.m[2][2]);
	Vector3 vdelta = world_location - cache::local_camera.location;

	float transformedX = vdelta.dot(vaxisy);
	float transformedY = vdelta.dot(vaxisz);
	float transformedZ = vdelta.dot(vaxisx);
	transformedZ = max(transformedZ, 1.0f);

	float fovFactor = settings::width / 2 / tanf(cache::local_camera.fov * M_PI / 360);
	float screenX = settings::width / 2 + transformedX * fovFactor / transformedZ;
	float screenY = settings::height / 2 - transformedY * fovFactor / transformedZ;

	return Vector2(screenX, screenY);
}

Vector3 world_to_screen(Vector3 WorldLocation)
{
	cache::local_camera = get_view_point();
	D3DMATRIX tempMatrix = to_matrix(cache::local_camera.rotation);
	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - cache::local_camera.location;
	Vector3 vTransformed = Vector3(vDelta.dot(vAxisY), vDelta.dot(vAxisZ), vDelta.dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	return Vector3(
		(settings::width / 2 / 2.0f) + vTransformed.x * (((settings::width / 2 / 2.0f) / tanf(cache::local_camera.fov * (float)M_PI / 360.f))) / vTransformed.z, (settings::height / 2 / 2.0f) - vTransformed.y * (((settings::height / 2 / 2.0f) / tanf(cache::local_camera.fov * (float)M_PI / 360.f))) / vTransformed.z, 0
	);
}

Vector3 get_entity_bone(uintptr_t mesh, int bone_id)
{
	uintptr_t bone_array = read<uintptr_t>(mesh + BONE_ARRAY);
	if (bone_array == 0)
		bone_array = read<uintptr_t>(mesh + BONE_ARRAY_CACHE);

	FTransform bone = read<FTransform>(bone_array + (bone_id * 0x60));
	FTransform component_to_world = read<FTransform>(mesh + COMPONENT_TO_WORLD);

	D3DMATRIX matrix = matrix_multiplication(bone.to_matrix_with_scale(), component_to_world.to_matrix_with_scale());

	return Vector3(matrix._41, matrix._42, matrix._43);
}

typedef struct visible_cached
{
	uintptr_t mesh;
	float last_submit_time_on_screen;
};

std::vector<visible_cached> visible_vec = {};

bool is_entity_visible(uintptr_t mesh)
{
	for (auto& cur_vv_enemy : visible_vec)
	{
		if (cur_vv_enemy.mesh == mesh)
		{
			float last_render_time_on_screen = read<float>(mesh + LAST_SUBMIT_TIME_ON_SCREEN);

			if (last_render_time_on_screen != 0.f && last_render_time_on_screen > cur_vv_enemy.last_submit_time_on_screen)
			{
				cur_vv_enemy.last_submit_time_on_screen = last_render_time_on_screen;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

std::string get_player_platform(uintptr_t player_state)
{
	std::string result;
	uintptr_t test_platform = read<uintptr_t>(player_state + PLATFORM);

	wchar_t platform[64];
	mem::read_physical((void*)test_platform, platform, sizeof(platform));

	std::wstring platform_wstr(platform);
	std::string platform_str(platform_wstr.begin(), platform_wstr.end());

	if (platform_str == "XBL")
	{
		result = "XBOX ONE";
	}
	else if (platform_str == "PSN")
	{
		result = "PLAYSTATION 4";
	}
	else if (platform_str == "PS5")
	{
		result = "PLAYSTATION 5";
	}
	else if (platform_str == "XSX")
	{
		result = "XBOX SERIES S/X";
	}
	else if (platform_str == "SWT")
	{
		result = "NINTENDO";
	}
	else if (platform_str == "WIN")
	{
		result = "WINDOWS";
	}
	else
	{
		result = "NPC";
	}

	return result;
}