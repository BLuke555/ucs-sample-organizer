#include <curses.h>
#include <stdio.h>
#include <stdbool.h>

#include "tui.h"



WINDOW *insertWin;
int position;


void tuiLog(char *log) {
	int i = 0;
	while (i < COLS) {
		move(LINES -1, i);
		printw(" ");
		i++;
	}

	mvprintw(LINES - 1, 1, ">_%s", log);
	refresh();
}


bool tuiInit() {
	struct AppState *as;

	// initialize ncurses. send all inputs to the program, and don't show any input
	initscr();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	noecho();
	// nodelay(stdscr, TRUE);

	return true;
}


void tuiWrite(struct AppState *as) {
	if (as->input != ERR && as->input >= 33 && as->input <= 126) {
		mvwprintw(insertWin, 1, position + 2, "%c_", as->input);
		position += 1;
		wrefresh(insertWin);
	}

	if (as->input == '\b') {
		if (position > 0) {
			position -= 1;
			mvwprintw(insertWin, 1, position + 2, "_  ");
			wrefresh(insertWin);
		}
	}

	// clear the screen
	if (as->input == '\n') {
		wclear(insertWin);
		wrefresh(insertWin);
	}
}


void tuiInsertString(struct AppState *as, char *string) {
	int height, width, starty, startx;
	height = 3;
	width = 90;
	startx = (COLS - width) / 2;
	starty = (LINES - height) / 2;

	int left, right, top, bottom, topleft, topright, botleft, botright;
	top = left = right = (int)' ';
	bottom = (int)'_';
	topleft = topright = botleft = botright = (int)' ';

	insertWin = newwin(height, width, starty, startx);
	refresh();

	wborder(insertWin, left, right, top, bottom, topleft, topright, botleft, botright);
	mvwprintw(insertWin, 0, 0, string);
	wrefresh(insertWin);
	
	position = 0;
	mvwprintw(insertWin, 1, position + 1, ">_");
	wrefresh(insertWin);

	as->state = INSERT;
}


bool tuiUpdate(struct AppState *as) {
	if (as->input == '\\') {
		return false;	
	} else if (as->input != ERR) {
		tuiLog((char *)&as->input);
	} 
	refresh();

	return true;
}

bool tuiDeinit() {
	endwin();
}
