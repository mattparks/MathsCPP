#include <cassert>
#include <sstream>
#include <iomanip>

export module MathsCPP:Colour;
export import :Vector;

namespace MathsCPP {
template<typename T/*, typename = std::enable_if_t<std::is_arithmetic_v<T>>*/>
class Colour {
public:
	/// In order of how bits are mapped [24, 16, 8, 0xFF].
	enum class Type {
		RGBA, ARGB, RGB
	};
	
	constexpr Colour() = default;
	constexpr Colour(T r, T g, T b, T a = 1) : r(r), g(g), b(b), a(a) {}
	constexpr Colour(uint32_t i, Type type = Type::RGB) {
		switch (type) {
		case Type::RGBA:
			r = static_cast<T>((uint8_t)(i >> 24 & 0xFF)) / 255.0f;
			g = static_cast<T>((uint8_t)(i >> 16 & 0xFF)) / 255.0f;
			b = static_cast<T>((uint8_t)(i >> 8 & 0xFF)) / 255.0f;
			a = static_cast<T>((uint8_t)(i & 0xFF)) / 255.0f;
			break;
		case Type::ARGB:
			r = static_cast<T>((uint8_t)(i >> 16)) / 255.0f;
			g = static_cast<T>((uint8_t)(i >> 8)) / 255.0f;
			b = static_cast<T>((uint8_t)(i & 0xFF)) / 255.0f;
			a = static_cast<T>((uint8_t)(i >> 24)) / 255.0f;
			break;
		case Type::RGB:
			r = static_cast<T>((uint8_t)(i >> 16)) / 255.0f;
			g = static_cast<T>((uint8_t)(i >> 8)) / 255.0f;
			b = static_cast<T>((uint8_t)(i & 0xFF)) / 255.0f;
			a = 1.0f;
			break;
		default:
			throw std::runtime_error("Unknown Color type");
		}
	}
	Colour(std::string hex, T a = 1) :
		a(a) {
		if (hex[0] == '#')
			hex.erase(0, 1);
		assert(hex.size() == 6);
		auto hexValue = std::stoul(hex, nullptr, 16);

		r = static_cast<float>((hexValue >> 16) & 0xff) / 255.0f;
		g = static_cast<float>((hexValue >> 8) & 0xff) / 255.0f;
		b = static_cast<float>((hexValue >> 0) & 0xff) / 255.0f;
	}
	template<typename T1>
	constexpr Colour(const Colour<T1> &c) { copy_cast(c.begin(), c.end(), begin()); }
	template<typename T1>
	constexpr explicit Colour(const Vector<T1, 4> &v) { copy_cast(v.begin(), v.end(), begin()); }

	template<typename T1>
	constexpr Colour &operator=(const Colour<T1> &v) {
		copy_cast(v.begin(), v.end(), begin());
		return *this;
	}

	constexpr const T &at(std::size_t i) const { return i == 0 ? r : i == 1 ? g : i == 2 ? b : a; }
	constexpr T &at(std::size_t i) { return i == 0 ? r : i == 1 ? g : i == 2 ? b : a; }
	
	constexpr const T &operator[](std::size_t i) const { return at(i); }
	constexpr T &operator[](std::size_t i) { return at(i); }

	auto begin() { return &at(0); }
	auto begin() const { return &at(0); }

	auto end() { return &at(0) + 4; }
	auto end() const { return &at(0) + 4; }

	constexpr const Vector<T, 2> &xy() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
	constexpr Vector<T, 2> &xy() { return *reinterpret_cast<Vector<T, 2> *>(this); }

	constexpr const Vector<T, 3> &xyz() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }
	constexpr Vector<T, 3> &xyz() { return *reinterpret_cast<Vector<T, 3> *>(this); }

	constexpr const Vector<T, 4> &xyzw() const { return *reinterpret_cast<const Vector<T, 4> *>(this); }
	constexpr Vector<T, 4> &xyzw() { return *reinterpret_cast<Vector<T, 4> *>(this); }

	/**
	 * Calculates the dot product of the this vector and another vector.
	 * @param other The other vector.
	 * @return The dot product.
	 */
	constexpr T Dot(const Colour &other) const {
		T result = 0;
		for (std::size_t i = 0; i < 4; i++)
			result += at(i) * other[i];
		return result;
	}

	/**
	 * Gets the length squared of this vector.
	 * @return The length squared.
	 */
	constexpr T Length2() const {
		return Dot(*this);
	}

	/**
	 * Gets the length of this vector.
	 * @return The length.
	 */
	auto Length() const {
		return std::sqrt(Length2());
	}

	/**
	 * Gets the unit vector of this vector.
	 * @return The normalized vector.
	 */
	auto Normalize() const {
		return *this / Length();
	}

	/**
	 * Calculates the linear interpolation between this colour and another colour.
	 * @param other The other quaternion.
	 * @param progression The progression.
	 * @return Left lerp right.
	 */
	template<typename T1, typename T2>
	constexpr Colour Lerp(const Colour<T1> &other, T2 progression) const {
		auto ta = *this * (1 - progression);
		auto tb = other * progression;
		return ta + tb;
	}

	/**
	 * Gets a colour representing the unit value of this colour.
	 * @return The unit colour.
	 */
	Colour GetUnit() const {
		auto l = Length();
		return {r / l, g / l, b / l, a / l};
	}

	/**
	 * Gets a packed integer representing this colour.
	 * @param type The order components of colour are packed.
	 * @return The packed integer.
	 */
	constexpr uint32_t GetInt(Type type = Type::RGBA) const {
		switch (type) {
		case Type::RGBA:
			return (static_cast<uint8_t>(r * 255.0f) << 24) | (static_cast<uint8_t>(g * 255.0f) << 16) | (static_cast<uint8_t>(b * 255.0f) << 8) | (static_cast<uint8_t>(a * 255.0f) &
				0xFF);
		case Type::ARGB:
			return (static_cast<uint8_t>(a * 255.0f) << 24) | (static_cast<uint8_t>(r * 255.0f) << 16) | (static_cast<uint8_t>(g * 255.0f) << 8) | (static_cast<uint8_t>(b * 255.0f) &
				0xFF);
		case Type::RGB:
			return (static_cast<uint8_t>(r * 255.0f) << 16) | (static_cast<uint8_t>(g * 255.0f) << 8) | (static_cast<uint8_t>(b * 255.0f) & 0xFF);
		default:
			throw std::runtime_error("Unknown Color type");
		}
	}
	
	/**
	 * Gets the hex code from this colour.
	 * @return The hex code.
	 */
	std::string GetHex() const {
		std::stringstream stream;
		stream << "#";

		auto hexValue = ((static_cast<uint32_t>(r * 255.0f) & 0xff) << 16) +
			((static_cast<uint32_t>(g * 255.0f) & 0xff) << 8) +
			((static_cast<uint32_t>(b * 255.0f) & 0xff) << 0);
		stream << std::hex << std::setfill('0') << std::setw(6) << hexValue;

		return stream.str();
	}

	template<typename T1>
	constexpr friend auto operator==(const Colour &lhs, const Colour<T1> &rhs) {
		for (std::size_t i = 0; i < 4; i++) {
			if (std::abs(lhs[i] - rhs[i]) > 0.0001f)
				return false;
		}
		return true;
	}

	template<typename T1>
	constexpr friend auto operator!=(const Colour &lhs, const Colour<T1> &rhs) {
		for (std::size_t i = 0; i < 4; i++) {
			if (std::abs(lhs[i] - rhs[i]) <= 0.0001f)
				return true;
		}
		return false;
	}

	constexpr friend auto operator+(const Colour &lhs) {
		Colour result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = +lhs[i];
		return result;
	}

	constexpr friend auto operator-(const Colour &lhs) {
		Colour result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = -lhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+(const Colour &lhs, const Colour<T1> &rhs) {
		Colour<decltype(lhs[0] + rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] + rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator-(const Colour &lhs, const Colour<T1> &rhs) {
		Colour<decltype(lhs[0] - rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] - rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator*(const Colour &lhs, const Colour<T1> &rhs) {
		Colour<decltype(lhs[0] * rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] * rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator/(const Colour &lhs, const Colour<T1> &rhs) {
		Colour<decltype(lhs[0] / rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] / rhs[i];
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(const Colour &lhs, T1 rhs) {
		Colour<decltype(lhs[0] * rhs)> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] * rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(const Colour &lhs, T1 rhs) {
		Colour<decltype(lhs[0] / rhs)> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs[i] / rhs;
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator*(T1 lhs, const Colour &rhs) {
		Colour<decltype(lhs * rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs * rhs[i];
		return result;
	}

	template<typename T1, typename = std::enable_if_t<std::is_arithmetic_v<T1>>>
	constexpr friend auto operator/(T1 lhs, const Colour &rhs) {
		Colour<decltype(lhs / rhs[0])> result;
		for (std::size_t i = 0; i < 4; i++)
			result[i] = lhs / rhs[i];
		return result;
	}

	template<typename T1>
	constexpr friend auto operator+=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs + rhs;
	}

	template<typename T1>
	constexpr friend auto operator-=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs - rhs;
	}

	template<typename T1>
	constexpr friend auto operator*=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs * rhs;
	}

	template<typename T1>
	constexpr friend auto operator/=(Colour &lhs, const T1 &rhs) {
		return lhs = lhs / rhs;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Colour &colour) {
		for (std::size_t i = 0; i < 4; i++)
			stream << colour[i] << (i != 4 - 1 ? ", " : "");
		return stream;
	}

	static const Colour Clear;
	static const Colour Black;
	static const Colour Grey;
	static const Colour Silver;
	static const Colour White;
	static const Colour Maroon;
	static const Colour Red;
	static const Colour Olive;
	static const Colour Yellow;
	static const Colour Green;
	static const Colour Lime;
	static const Colour Teal;
	static const Colour Aqua;
	static const Colour Navy;
	static const Colour Blue;
	static const Colour Purple;
	static const Colour Fuchsia;

	T r{}, g{}, b{}, a{1};
};

template<typename T>
const Colour<T> Colour<T>::Clear(0x00000000, Type::RGBA);
template<typename T>
const Colour<T> Colour<T>::Black(0x000000FF, Type::RGBA);
template<typename T>
const Colour<T> Colour<T>::Grey(0x808080);
template<typename T>
const Colour<T> Colour<T>::Silver(0xC0C0C0);
template<typename T>
const Colour<T> Colour<T>::White(0xFFFFFF);
template<typename T>
const Colour<T> Colour<T>::Maroon(0x800000);
template<typename T>
const Colour<T> Colour<T>::Red(0xFF0000);
template<typename T>
const Colour<T> Colour<T>::Olive(0x808000);
template<typename T>
const Colour<T> Colour<T>::Yellow(0xFFFF00);
template<typename T>
const Colour<T> Colour<T>::Green(0x00FF00);
template<typename T>
const Colour<T> Colour<T>::Lime(0x008000);
template<typename T>
const Colour<T> Colour<T>::Teal(0x008080);
template<typename T>
const Colour<T> Colour<T>::Aqua(0x00FFFF);
template<typename T>
const Colour<T> Colour<T>::Navy(0x000080);
template<typename T>
const Colour<T> Colour<T>::Blue(0x0000FF);
template<typename T>
const Colour<T> Colour<T>::Purple(0x800080);
template<typename T>
const Colour<T> Colour<T>::Fuchsia(0xFF00FF);

using Colourf = Colour<float>;
using Colourd = Colour<double>;
using Colouri = Colour<int32_t>;
using Colourui = Colour<uint32_t>;
}

/*export template<typename T>
struct std::hash<MathsCPP::Colour<T>> {
	size_t operator()(const MathsCPP::Colour<T> &colour) const noexcept {
		size_t seed = 0;
		for (size_t i = 0; i < 4; i++)
			MathsCPP::HashCombine(seed, colour[i]);
		return seed;
	}
};*/
