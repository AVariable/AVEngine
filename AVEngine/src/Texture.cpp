#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include "Renderer.h"

Texture::Texture(const std::string& path) :
	_rendererId(0),
	_filepath(path),
	_localBuffer(nullptr),
	_width(0),
	_height(0),
	_bytesPerPixel(0) {
	stbi_set_flip_vertically_on_load(1);
	_localBuffer = stbi_load(path.c_str(), &_width, &_height, &_bytesPerPixel, 4);

	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, _rendererId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (_localBuffer != nullptr) {
		stbi_image_free(_localBuffer);
		_localBuffer = nullptr;
	}
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &_rendererId));
}

void Texture::Bind(unsigned slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, _rendererId));
}

void Texture::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}