#pragma once
class Attenuation
{
	public:
		Attenuation(float constant, float linear, float quadratic);

	private:
		const float constant;
		const float linear;
		const float quadratic;
};

