#pragma once

#include "bitmanipulations.hpp"
#include <iostream>
#include <bitset>
#include <vector>
#include <array>

using color = int;
const color black = 0;
const color white = 1;
const color empty = 2;
const color draw = -1;

void show_binary(uint64 bits);

class poseval{
public:
	uint64 pos;
	int eval;
	poseval(){
		init();
	};
	void init(){
		pos = 0;
		eval = 0;
	};
};

bool comp(const poseval a, const poseval b);

class log{
public:
	uint64 data[2];
	color put_color;
	bool pass;
	uint64 mobility;
	std::array<poseval, 32> mobility_list;			//そのturnでの手はmobility_listに含まれる手が選択される。そのため、put_colorのmobilityである。

	log(){
		init();
	}
	inline void init(){
		data[white] = 0;
		data[black] = 0;
		put_color = empty;
		pass = false;
		mobility = 0;
		for (poseval &mobility: mobility_list){
			mobility.init();
		}
	}
	inline void expandmobility(){
		int idx = 0;
		for (uint64 i = 1; i != 0; i<<=1) {
			if ((mobility & i) != 0) {
				mobility_list[idx].pos = i;
				idx++;
			}
		}
	}
};

class board {
private:
	uint64 data[2];
	int turn;
	color current_color;

	uint64 getflipdiscs(const uint64 put, const color c) const;
	std::array<int, 1<<16> hash_array;
public:
	int countdiscs(const color c)const;
	board();
	~board();
	void init();
	std::array<log, 128> history;

	inline int getturn()const {
		return turn;
	}
	inline uint64 getboard(const color c) const{
		return data[c];
	}
	inline int getcurrentcolor()const {
		return current_color;
	}

	bool isgameover()const;
	color jadge() const;

	uint64 checkcurrentmobility();
	bool putdisc(const uint64 pos);
	bool pass();
	bool undo();

	uint64 checkmobility(const color c) const;
	uint64 getblank();
	uint64 getcornerdiscs(const color c) const;
	uint64 getstablediscs(const color c)const;

	void set(const uint64 idx, const color c);
	color check(const uint64 idx)const;

	void showCUI()const;
	void setCUI();
	uint64 coordinateToIdx(const char x, const char y)const;

	unsigned int gethash();
	void inithasharray();
	void addhash(const unsigned int idx, const int eval);
	bool checkhash(const unsigned int idx, const int eval) const;//重複判定 重複があればtrue, なければfalse
	int gethasheval(const unsigned int idx)const;
};
