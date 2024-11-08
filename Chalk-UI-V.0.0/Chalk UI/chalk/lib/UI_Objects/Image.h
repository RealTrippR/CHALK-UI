#ifndef CHK_IMAGE_HPP
#define CHK_IMAGE_HPP

namespace chk {
	class image : public UI_Object {
	public:
		void draw(sf::RenderTexture& Parent_RT) override {
			Parent_RT.draw(M_Rect);
		}
	protected:
		inline void updateColorAndTexture() {
			M_Rect.setFillColor(M_FillColor);
			M_Rect.setTexture(&M_Texture,true);
		}

		inline void updateTransform(bool callToParent = false) override {
			updateTransformUI_Object();
			M_Rect.setSize(getSizePixels());
			M_Rect.setPosition(getPositionPixels());
			updateColorAndTexture();
		}
	public:
		// GETTERS

		sf::Image getImage() {
			return M_Image;
		}

		sf::Image& getImageAsRef() {
			return M_Image;
		}

		sf::Color getPixel(int x, int y) {
			return M_Image.getPixel(x, y);
		}

		// returns the size of the image as it is in disk
		sf::Vector2u getImageSize() {
			return M_Image.getSize();
		}

	public:

		sf::Vector2f getPosition() {
			return M_Rect.getPosition();
		}

		void setPosition(UI_Vector2f position) {
			M_Position = position;
			updateTransform();
			refresh();
		}

		sf::Vector2f getSize() {
			return M_Rect.getSize();
		}

		void setSize(UI_Vector2f size) {
			M_Size = size;
			updateTransform();
			refresh();
		}

		void setFillColor(sf::Color fillColor) {
			M_FillColor = fillColor;
			updateTransform();
			refresh();
		}

		sf::Color getFillColor() {
			return M_FillColor;
		}

		void setOutlineColor(sf::Color outlineColor) {
			M_Rect.setOutlineColor(outlineColor);
			refresh();
		}

		sf::Color getOutlineColor() {
			return M_Rect.getOutlineColor();
		}

		void setOutlineThickness(int thickness) {
			M_Rect.setOutlineThickness(thickness);
			refresh();
		}

		int getOutlineThickness() {
			return M_Rect.getOutlineThickness();
		}
	public:
		// SETTERS
		void setImage(std::string path) {
			M_Image.loadFromFile(fs::absolute(path).string());
			M_Texture.loadFromImage(M_Image);
			updateTransform();
			refresh();
		}

		void setPixel(int x, int y, sf::Color color) {
			M_Image.setPixel(x, y, color);
			refresh();
		}

		image() {
			setImage("..\\Chalk UI\\default assets\\Default_Image.png");
		}
	
	private:
		sf::Image M_Image;
		sf::Texture M_Texture;
		sf::RectangleShape M_Rect;

		sf::Color M_FillColor = sf::Color::White;
	};
}

#endif // !CHK_IMAGE_H