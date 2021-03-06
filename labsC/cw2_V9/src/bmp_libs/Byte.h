#pragma once
#include <fstream>
#include <vector>

namespace Byte{
	//Little Endian
	u_int16_t make_short(u_char c1, u_char c2) {
		return (short(c2) << 8) + short(c1);
	}

	u_int make_int(u_char c1, u_char c2, u_char c3, u_char c4) {
		return ((u_int)make_short(c3,c4) << 16) + make_short(c1,c2);
	}

	std::vector<u_int16_t> int_to_short(u_int num){
		u_short val1 = num >> 16;
		u_short val2 = num & ((1 << 16) - 1);
		return {val2, val1};
	}

	std::vector<u_char> short_to_byte(u_int16_t num){
		u_char val1 = num >> 8;
		u_char val2 = num & ((1 << 8) - 1);
		return {val2, val1};
	}
	std::vector<u_char> int_to_byte(u_int num){
		const auto item1 = short_to_byte(num);
		const auto item2 = short_to_byte(num >> 16);
		return {item1[0], item1[1], item2[0], item2[1]};
	}

	bool compare_like_short(u_int16_t src, u_char c1, u_char c2) {
		return src == make_short(c1,c2);
	}

	bool compare_like_int(u_int src, u_char c1, u_char c2, u_char c3, u_char c4) {
		return compare_like_short(src >> 16,c1,c2) && compare_like_short(src,c3,c4);
	}

	void write_16_like_byte(u_int16_t item, std::ostream& out){
		auto int16 = short_to_byte(item);
		out << int16[0] << int16[1];
	}

	void write_32_like_byte(u_int item, std::ostream& out){
		auto int32 = int_to_byte(item);
		out << int32[0] << int32[1] << int32[2] << int32[3];
	}

	std::vector<u_char> get_byte(std::fstream& in, int cnt){
		std::vector<u_char> byte(cnt);
		for (unsigned char & item : byte) {
			item = in.get();
		}
		return byte;
	}
}
