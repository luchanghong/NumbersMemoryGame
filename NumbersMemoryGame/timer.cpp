/*******************************************************
* 计时器模块函数
* 函数前缀：NMG_timer_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <time.h>
#include <stdio.h>
#include <process.h>

enum {
	hold_on, counting, pause
} timer_status;

static clock_t start_time;			// 开启计时器时间
static clock_t last_counting_time;	// 上次计时器更新时间
static clock_t pause_at;			// 点击暂停的时间
static clock_t play_at;				// 恢复暂停的时间
static clock_t paused_time;			// 暂停经历的时间
extern void NMG_view_show_game_timer(int hour, int min, int sec);

// 开始计时
void NMG_timer_start() {
	if (timer_status == hold_on){
		timer_status = counting;
		paused_time = 0;
		start_time = last_counting_time = clock();
	}
}

// 计时器更新
void NMG_timer_update(void *) {
	while (true){
		if (timer_status == counting){
			clock_t current_time = clock();
			int seconds = (current_time - last_counting_time) / CLOCKS_PER_SEC;
			if (seconds >= 1){
				seconds = (current_time - start_time - paused_time) / CLOCKS_PER_SEC;
				//printf("current %ld\t last %ld\n", current_time, last_counting_time);
				int sec = seconds % 60,
					min = (seconds / 60) % 60,
					hour = (seconds / 60 * 60) % 60;
				NMG_view_show_game_timer(hour, min, sec);
				last_counting_time = current_time;
			}
		}
	}
	_endthread();
}

// 暂停计时
void NMG_timer_pause() {
	timer_status = pause;
	pause_at = clock();
}

// 恢复计时
void NMG_timer_play() {
	timer_status = counting;
	play_at = clock();
	paused_time += play_at - pause_at;
}

// 重置计时
void NMG_timer_reset() {
	timer_status = hold_on;
	pause_at = 0;
	play_at = 0;
	paused_time = 0;
	NMG_view_show_game_timer(0, 0, 0);
}

/*
* 取代Sleep()的阻塞函数
* 
* @param int seconds 要阻塞的秒数
* @return void
*/
void NMG_timer_block(int seconds) {
	clock_t start = clock();
	while (true){
		int t = (clock() - start) / CLOCKS_PER_SEC;
		if (t >= seconds){
			return;
		}
		//NMG_timer_update(NULL);
	}
}