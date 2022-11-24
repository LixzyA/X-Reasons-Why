#include"input.h"

ExMessage m;
void getinput() {
	m = getmessage(EM_KEY | EM_MOUSE);
}