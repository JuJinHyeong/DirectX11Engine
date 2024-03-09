#pragma once
#define HR(hr, msg) {if(FAILED(hr)) {OutputDebugString(msg); exit(-1);}}

class ErrorLogger {
public:
	
};