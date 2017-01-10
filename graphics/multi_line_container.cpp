#include "multi_line_container.hpp"
#include "managers/font_manager.hpp"

#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace graphics {

MultiLineContainer::MultiLineContainer(const std::string& font_name, uint character_size, const sf::Color& color, const sf::FloatRect& bounds, float padding)
  : _font {font::FontManager::get(font_name)}
  , _color {color}
  , _character_size {character_size}
  , _bounds {bounds}
  , _line_padding {padding}
{}

void MultiLineContainer::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  const std::vector<TextSP>& texts = current();
  for(const TextSP& text : texts)
    text->draw(target, states);
}

void MultiLineContainer::update(const sf::Time& elapsed_time)
{
  if(!_text_appearance)
    return;

  _text_appearance->update(elapsed_time);

  if(_text_appearance->isFinished())
  {
    TextSP next_text;

    // Find next line to animate
    const std::vector<TextSP>& lines = current();
    for(size_t i = 0, n = lines.size(); i < n; ++i)
    {
      if(lines[i] == _text_appearance->text())
      {
        if(i != n - 1)
          next_text = lines[i + 1];
        break;
      }
    }

    if(next_text)
      setTextAppearance(next_text);
    else
      _text_appearance.reset();
  }
}

void MultiLineContainer::setTextAppearance(TextSP& text)
{
  _text_appearance.reset(new animations::TextAppearance{text, sf::milliseconds(500)});
}

void MultiLineContainer::updatePosition(float x, float y)
{
  for(std::vector<TextSP>& text : _texts)
  {
    float current_y {y};

    for(TextSP& line : text)
    {
      line->setPosition(x, current_y);
      current_y += line->getGlobalBounds().height + _line_padding;
    }
  }
}

float MultiLineContainer::currentTextHeight() const
{
  float total {0};

  const auto& lines = current();
  for(const auto& line : lines)
    total += line->getGlobalBounds().height + _line_padding;

  return total;
}

TextSP MultiLineContainer::addNewLine()
{
  if(currentTextHeight() >= _bounds.height)
  {
    _texts.resize(_texts.size() + 1);
    _current_text++;
  }

  TextSP text = graphics::getText(_font, "", _character_size, _color);
  text->hide();
  _texts[_texts.size() - 1].push_back(text);
  return text;
}

void MultiLineContainer::setString(const std::string& text)
{
  _current_text = 0;
  _texts.clear();
  _texts.resize(1);
  TextSP line = addNewLine();
  sf::String text_content, text_content_tmp;

  std::vector<std::string> words;
  boost::algorithm::split(words, text, boost::is_any_of(" "));
  for(const std::string& word : words)
  {
    text_content_tmp += word + " ";
    line->setString(text_content_tmp);

    if(line->getGlobalBounds().width > _bounds.width)
    {
      line->setString(text_content);
      line = addNewLine();
      text_content_tmp = "";
    }
    else
    {
      text_content = text_content_tmp;
    }
  }

  _current_text = 0;

  updatePosition(_position.x, _position.y);
  if(!_texts.empty() && !_texts[0].empty())
    setTextAppearance(_texts[0][0]);
}

bool MultiLineContainer::next() noexcept
{
  if(_current_text == _texts.size() - 1)
    return false;

  _current_text++;
  setTextAppearance(_texts[_current_text][0]);

  return true;
}

bool MultiLineContainer::hasNext() const noexcept
{
  const size_t nbr_texts {_texts.size()};
  return nbr_texts > 1 && _current_text != nbr_texts;
}

bool MultiLineContainer::isCurrentShown() const noexcept
{
  return !_text_appearance;
}

bool MultiLineContainer::isAllShown() const noexcept
{
  return _current_text == _texts.size() - 1 && !_text_appearance;
}

void MultiLineContainer::finishAnimation() noexcept
{
  if(!_text_appearance)
    return;

  _text_appearance->finish();
  _text_appearance.reset();

  std::vector<TextSP>& lines = current();
  for(TextSP& line : lines)
    line->show();
}

sf::FloatRect MultiLineContainer::getGlobalBounds() const
{
  return _bounds;
}

}
