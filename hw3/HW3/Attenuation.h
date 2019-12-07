#pragma once

#include <tuple>

class Attenuation
{
	public:
		Attenuation(float constant, float linear, float quadratic);
		~Attenuation();

		// Getters
		float constant() const;
		float linear() const;
		float quadratic() const;
		std::tuple<float, float, float> values() const;

	private:
		const float _constant;
		const float _linear;
		const float _quadratic;
};

