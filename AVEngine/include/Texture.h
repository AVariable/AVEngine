#pragma once

#include <string>

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return _width; }
	inline int GetHeight() const { return _height; }

private:
	unsigned _rendererId;
	std::string _filepath;
	unsigned char* _localBuffer;
	int _width;
	int _height;
	int _bytesPerPixel;
};