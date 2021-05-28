void f() {
	const char html[8];
	vulnerable();
	add_to_dom(html);
}

void vulnerable() {
	char vuln_buffer[8];
	copy_user_input_to_buffer(vuln_buffer);
}



