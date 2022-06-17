#include"ImageTexture.h"

/* Constructor / Distructor */
ImageTexture::ImageTexture(const sf::Vector2f& CenterPos, const Bg_t& objectTex, const sf::Vector2f& factor)
	:Image()
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	m_sprite.setTexture(*texture);
	setSize(sf::Vector2u(factor));
	setPosition(CenterPos);
}

ImageTexture::ImageTexture(const sf::Vector2f& CenterPos, const Dynamic_t& objectTex, const sf::Vector2f& factor)
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	initImage(CenterPos, texture, factor);
}

ImageTexture::ImageTexture(const sf::Vector2f& CenterPos, const Fighter_f& objectTex, const sf::Vector2f& factor)
	:Image()
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	initImage(CenterPos, texture, factor);
}

ImageTexture::ImageTexture(const sf::Vector2f& CenterPos, const FighterIcon_f& objectTex, const sf::Vector2f& factor)
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	initImage(CenterPos, texture, factor);
}

ImageTexture::ImageTexture( const sf::Vector2f& CenterPos, const sf::Vector2f& factor)
	:Image()
{
	m_sprite.setPosition(CenterPos);
	m_sprite.setScale(factor);
}

void ImageTexture::initImage(const sf::Vector2f& CenterPos, sf::Texture* texture, const sf::Vector2f& factor)
{
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(float(texture->getSize().x / 2), float(texture->getSize().y / 2));
	m_sprite.setScale(factor);
	setPosition(CenterPos);
}

/* Accesors */
sf::FloatRect ImageTexture::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f ImageTexture::getPosition() const
{
	return m_sprite.getPosition();
}

sf::Vector2f ImageTexture::getSize() const
{
	return sf::Vector2f( float( m_sprite.getTextureRect().width ), float( m_sprite.getTextureRect().height ) );
}

float ImageTexture::getFactor() const
{
	return m_sprite.getScale().x;
}

/* Mutator */
void ImageTexture::setPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition( pos );
}

void ImageTexture::setSize( const sf::Vector2u size )
{
	m_sprite.scale( ( size.x / m_sprite.getGlobalBounds().width ), ( size.y / m_sprite.getGlobalBounds().height ) );
}

void ImageTexture::setTexture(const Fighter_f& objectTex)
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	m_sprite.setTexture(*texture);
}

void ImageTexture::setTexture(const FighterIcon_f& objectTex)
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	m_sprite.setTexture(*texture);
}

void ImageTexture::setTexture(const Bg_t& objectTex)
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	m_sprite.setTexture(*texture);
}

void ImageTexture::setTexture(const Dynamic_t& objectTex)
{
	sf::Texture* texture = ResourceManager::instance().getTexture(objectTex);
	m_sprite.setTexture(*texture);
}

void ImageTexture::setOrigin(const float x, const float y)
{
	m_sprite.setOrigin(x, y);
}

void ImageTexture::setScale( const float x, const float y)
{
	m_sprite.setScale( sf::Vector2f( x, y ) );
}


/* Draw */
void ImageTexture::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}