#pragma once

class MathUtils
{
public:
	static bool fuzzyEquals(float a, float b, float var);
	static float clamp(float n, float lower, float upper);
	static int clamp(int n, int lower, int upper);
	static float wrappingNormalize(float value, float start, float end);
	static int wrappingNormalize(int value, int start, int end);
};
