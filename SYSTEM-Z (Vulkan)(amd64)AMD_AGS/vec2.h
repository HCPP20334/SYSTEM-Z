
// github.com/hcpp20334 
// vec2.h - lib to x,y vectors integers and float64, double64
#include <stdint.h>
#include <iostream>
#include <assert.h>
typedef long double double64_t;
typedef long float float64_t;
struct i64Vec2
{
	int64_t                                   x, y;
	constexpr i64Vec2() : x(0.0f), y(0.0f) {}
	constexpr i64Vec2(int64_t _x, int64_t _y) : x(_x), y(_y) {}
	int64_t& operator[] (size_t idx) { assert(idx == 0 || idx == 1); return ((int64_t*)(void*)(char*)this)[idx]; }
	int64_t  operator[] (size_t idx) const { assert(idx == 0 || idx == 1); return ((const int64_t*)(const void*)(const char*)this)[idx]; }
};
struct i32Vec2
{
	int32_t                                   x, y;
	constexpr i32Vec2() : x(0.0f), y(0.0f) {}
	constexpr i32Vec2(int32_t _x, int32_t _y) : x(_x), y(_y) {}
	int32_t& operator[] (size_t idx) { assert(idx == 0 || idx == 1); return ((int32_t*)(void*)(char*)this)[idx]; }
	int32_t  operator[] (size_t idx) const { assert(idx == 0 || idx == 1); return ((const int32_t*)(const void*)(const char*)this)[idx]; }
};
struct i16Vec2
{
	int16_t                                   x, y;
	constexpr i16Vec2() : x(0.0f), y(0.0f) {}
	constexpr i16Vec2(int16_t _x, int16_t _y) : x(_x), y(_y) {}
	int16_t& operator[] (size_t idx) { assert(idx == 0 || idx == 1); return ((int16_t*)(void*)(char*)this)[idx]; }
	int16_t  operator[] (size_t idx) const { assert(idx == 0 || idx == 1); return ((const int16_t*)(const void*)(const char*)this)[idx]; }
};
struct i8Vec2
{
	int8_t                                   x, y;
	constexpr i8Vec2() : x(0.0f), y(0.0f) {}
	constexpr i8Vec2(int8_t _x, int8_t _y) : x(_x), y(_y) {}
	int8_t& operator[] (size_t idx) { assert(idx == 0 || idx == 1); return ((int8_t*)(void*)(char*)this)[idx]; }
	int8_t  operator[] (size_t idx) const { assert(idx == 0 || idx == 1); return ((const int8_t*)(const void*)(const char*)this)[idx]; }
};
struct d64Vec2
{
	double64_t                                   x, y;
	constexpr d64Vec2() : x(0.0f), y(0.0f) {}
	constexpr d64Vec2(double64_t _x, double64_t _y) : x(_x), y(_y) {}
	double64_t& operator[] (size_t idx) { assert(idx == 0 || idx == 1); return ((double64_t*)(void*)(char*)this)[idx]; }
	double64_t  operator[] (size_t idx) const { assert(idx == 0 || idx == 1); return ((const double64_t*)(const void*)(const char*)this)[idx]; }
};
struct f64Vec2
{
	float64_t                                   x, y;
	constexpr f64Vec2() : x(0.0f), y(0.0f) {}
	constexpr f64Vec2(float64_t _x, float64_t _y) : x(_x), y(_y) {}
	float64_t& operator[] (size_t idx) { assert(idx == 0 || idx == 1); return ((float64_t*)(void*)(char*)this)[idx]; }
	float64_t  operator[] (size_t idx) const { assert(idx == 0 || idx == 1); return ((const float64_t*)(const void*)(const char*)this)[idx]; }
};
int64_t i64Vec2Size() {
	return sizeof(i64Vec2);
}
int64_t i32Vec2Size() {
	return sizeof(i32Vec2);
}
int64_t i16Vec2Size() {
	return sizeof(i16Vec2);
}
int64_t i8Vec2Size() {
	return sizeof(i8Vec2);
}
int64_t d64Vec2Size() {
	return sizeof(d64Vec2);
}
int64_t f64Vec2Size() {
	return sizeof(f64Vec2);
}
void GetAllVec2Size() {
	std::cout << "i64V2:" << i64Vec2Size() << std::endl;
	std::cout << "i32V2:" << i32Vec2Size() << std::endl;
	std::cout << "i16V2:" << i16Vec2Size() << std::endl;
	std::cout << "i8V2:"  << i8Vec2Size() << std::endl;
	std::cout << "d64V2:" << d64Vec2Size() << std::endl;
	std::cout << "f64V2:" << f64Vec2Size() << std::endl;
}