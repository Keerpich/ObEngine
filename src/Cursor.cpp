#include "Cursor.hpp"

namespace mse
{
	namespace Cursor
	{
		Cursor::Cursor()
		{
		}
		Cursor::Cursor(sf::RenderWindow* window) : cursorAnim(System::Path("Sprites/Cursors/Round"))
		{
			this->window = window;
			cursorAnim.loadAnimator();
			cursorAnim.setKey("IDLE");

			cursorTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Cursor")
				->addTrigger("Clicked")
				->addTrigger("Pressed")
				->addTrigger("Released");
		}

		Cursor::~Cursor()
		{
			Script::TriggerDatabase::GetInstance()->removeTriggerGroup(cursorTriggers);
		}

		void Cursor::selectCursor(std::string cursor)
		{
			cursorAnim.clear();
			cursorAnim = Animation::Animator(System::Path("Sprites/Cursors/").add(cursor).toString());
			cursorAnim.loadAnimator();
			cursorAnim.setKey("IDLE");
			cursorAnim.update();
			cursorSprite = cursorAnim.getSprite();
		}

		void Cursor::selectKey(std::string key)
		{
			cursorAnim.setKey(key);
		}

		int Cursor::getX()
		{
			return x;
		}

		int Cursor::getY()
		{
			return y;
		}

		void Cursor::setX(int newx)
		{
			this->x = newx;
			sf::Mouse::setPosition(sf::Vector2i(this->x, this->y));
		}

		void Cursor::setY(int newy)
		{
			this->y = newy;
			sf::Mouse::setPosition(sf::Vector2i(this->x, this->y));
		}

		void Cursor::setPosition(int newx, int newy)
		{
			this->x = newx;
			this->y = newy;
			sf::Mouse::setPosition(sf::Vector2i(this->x, this->y));
		}

		void Cursor::update()
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftclicked)
			{
				leftclicked = true;
				leftfirstclic = true;
				leftReleased = false;
				cursorAnim.setKey("CLIC");
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftclicked)
			{
				leftclicked = false;
				leftfirstclic = false;
				leftReleased = true;
				cursorAnim.setKey("RELEASE");
			}
			else
			{
				leftfirstclic = false;
				leftReleased = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rightclicked)
			{
				rightclicked = true;
				rightfirstclic = true;
				rightReleased = false;
				cursorAnim.setKey("CLIC");
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && rightclicked)
			{
				rightclicked = false;
				rightfirstclic = false;
				rightReleased = true;
				cursorAnim.setKey("RELEASE");
			}
			else
			{
				rightfirstclic = false;
				rightReleased = false;
			}
			if (!leftclicked && !rightclicked && cursorAnim.getKey() == "HOLD")
				cursorAnim.setKey("RELEASE");
			cursorAnim.update();
			if (cursorAnim.textureChanged())
			{
				cursorSprite = cursorAnim.getSprite();
			}
			if (doesUpdateOutsideWindow)
			{
				x = sf::Mouse::getPosition().x - window->getPosition().x;
				y = sf::Mouse::getPosition().y - window->getPosition().y;
				if (x < 0) x = 0;
				if (x > window->getSize().x) x = window->getSize().x;
				if (y < 0) y = 0;
				if (y > window->getSize().y) y = window->getSize().y;
			}
			else
			{
				if (sf::Mouse::getPosition().x - window->getPosition().x > 0 && sf::Mouse::getPosition().y - window->getPosition().y > 0)
				{
					if (sf::Mouse::getPosition().x - window->getPosition().x < window->getSize().x && sf::Mouse::getPosition().y - window->getPosition().y < window->getSize().y)
					{
						x = sf::Mouse::getPosition().x - window->getPosition().x;
						y = sf::Mouse::getPosition().y - window->getPosition().y;
						if (x < 0) x = 0;
						if (x > window->getSize().x) x = window->getSize().x;
						if (y < 0) y = 0;
						if (y > window->getSize().y) y = window->getSize().y;
					}
				}
			}
			cursorSprite->setPosition(x, y);
		}

		void Cursor::handleTriggers()
		{
			if (this->getClicked("Left"))
			{
				cursorTriggers->pushParameter("Clicked", "Key", std::string("Left"));
				cursorTriggers->pushParameter("Clicked", "X", this->x);
				cursorTriggers->pushParameter("Clicked", "Y", this->y);
				cursorTriggers->enableTrigger("Clicked");
			}
			if (this->getClicked("Right"))
			{
				cursorTriggers->pushParameter("Clicked", "Key", std::string("Right"));
				cursorTriggers->pushParameter("Clicked", "X", this->x);
				cursorTriggers->pushParameter("Clicked", "Y", this->y);
				cursorTriggers->enableTrigger("Clicked");
			}
			if (this->getPressed("Left"))
			{
				cursorTriggers->pushParameter("Pressed", "Key", std::string("Left"));
				cursorTriggers->pushParameter("Pressed", "X", this->x);
				cursorTriggers->pushParameter("Pressed", "Y", this->y);
				cursorTriggers->enableTrigger("Pressed");
			}
			if (this->getPressed("Right"))
			{
				cursorTriggers->pushParameter("Pressed", "Key", std::string("Right"));
				cursorTriggers->pushParameter("Pressed", "X", this->x);
				cursorTriggers->pushParameter("Pressed", "Y", this->y);
				cursorTriggers->enableTrigger("Pressed");
			}
			if (this->getReleased("Left"))
			{
				cursorTriggers->pushParameter("Released", "Key", std::string("Left"));
				cursorTriggers->pushParameter("Released", "X", this->x);
				cursorTriggers->pushParameter("Released", "Y", this->y);
				cursorTriggers->enableTrigger("Released");
			}
			if (this->getReleased("Right"))
			{
				cursorTriggers->pushParameter("Released", "Key", std::string("Right"));
				cursorTriggers->pushParameter("Released", "X", this->x);
				cursorTriggers->pushParameter("Released", "Y", this->y);
				cursorTriggers->enableTrigger("Released");
			}
		}

		void Cursor::updateOutsideWindow(bool state)
		{
			doesUpdateOutsideWindow = state;
		}

		bool Cursor::getPressed(std::string clic)
		{
			if (clic == "Left")
				return leftclicked;
			else if (clic == "Right")
				return rightclicked;
			else
				return false;
		}

		bool Cursor::getClicked(std::string clic)
		{
			if (clic == "Left")
				return leftfirstclic;
			else if (clic == "Right")
				return rightfirstclic;
			else
				return false;
		}

		bool Cursor::getReleased(std::string clic)
		{
			if (clic == "Left")
				return leftReleased;
			else if (clic == "Right")
				return rightReleased;
			else
				return false;
		}

		sf::Sprite* Cursor::getSprite()
		{
			return cursorSprite;
		}
	}
}