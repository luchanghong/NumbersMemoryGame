/*******************************************************
* ��ʱ��ģ�麯��
* ����ǰ׺��NMG_timer_
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

static clock_t start_time;			// ������ʱ��ʱ��
static clock_t last_counting_time;	// �ϴμ�ʱ������ʱ��
static clock_t pause_at;			// �����ͣ��ʱ��
static clock_t play_at;				// �ָ���ͣ��ʱ��
static clock_t paused_time;			// ��ͣ������ʱ��
extern void NMG_view_show_game_timer(int hour, int min, int sec);

// ��ʼ��ʱ
void NMG_timer_start() {
	if (timer_status == hold_on){
		timer_status = counting;
		paused_time = 0;
		start_time = last_counting_time = clock();
	}
}

// ��ʱ������
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

// ��ͣ��ʱ
void NMG_timer_pause() {
	timer_status = pause;
	pause_at = clock();
}

// �ָ���ʱ
void NMG_timer_play() {
	timer_status = counting;
	play_at = clock();
	paused_time += play_at - pause_at;
}

// ���ü�ʱ
void NMG_timer_reset() {
	timer_status = hold_on;
	pause_at = 0;
	play_at = 0;
	paused_time = 0;
	NMG_view_show_game_timer(0, 0, 0);
}

/*
* ȡ��Sleep()����������
* 
* @param int seconds Ҫ����������
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