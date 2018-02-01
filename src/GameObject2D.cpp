#include "GameObject2D.h"


Graphics::GameObject2D::GameObject2D(SDL_Texture *gTexture,
		Geometry::Shape *shape,
		Collisions::BoundBox *topBox,
		Collisions::BoundBox *leftBox,
		Collisions::BoundBox *botBox,
		Collisions::BoundBox *rightBox) {
	this->gTexture = gTexture;
	this->shape = shape;

	// move relevant to real positions
	if (topBox != NULL) {
		topBox->setX(shape->getX() + topBox->getX());
		topBox->setY(shape->getY() + topBox->getY());
	}
	
	if (leftBox != NULL) {
		leftBox->setX(shape->getX() + leftBox->getX());
		leftBox->setY(shape->getY() + leftBox->getY());
	}
	
	if (botBox != NULL) {
		botBox->setX(shape->getX() + botBox->getX());
		botBox->setY(shape->getY() + botBox->getY());
	}

	if (rightBox != NULL) {
		rightBox->setX(shape->getX() + rightBox->getX());
		rightBox->setY(shape->getY() + rightBox->getY());
	}
	
	boxes[Object2DSide::TOP] = topBox;
	boxes[Object2DSide::LEFT] = leftBox;
	boxes[Object2DSide::BOT] = botBox;
	boxes[Object2DSide::RIGHT] = rightBox;

	velX = 0;
	velY = 0;
}


Graphics::GameObject2D::GameObject2D(GameObject2D& go2d) {
	printf("Calling");
	gTexture = go2d.getTexture();
	shape = go2d.getShape();

	boxes[Object2DSide::TOP] = go2d.getBoxes()[0];
	boxes[Object2DSide::LEFT] = go2d.getBoxes()[1];
	boxes[Object2DSide::BOT] = go2d.getBoxes()[2];
	boxes[Object2DSide::RIGHT] = go2d.getBoxes()[3];
	
	velX = go2d.getVelX();
	velY = go2d.getVelY();
}


Graphics::GameObject2D::GameObject2D(const GameObject2D& go2d) {
	printf("Called.");
}


Graphics::GameObject2D::~GameObject2D() {
// @uncoment
	//printf("[GO2D] Calling destructor.\n");
	if (gTexture != NULL) {
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
	
	if (shape != NULL) {
		delete shape;
		shape = NULL;
	}

	for (int i = 0; i < OBJECT_2D_SIDES; i++) {
		if (boxes[i] == NULL) continue;
		delete boxes[i];
	} 
}


void Graphics::GameObject2D::render(SDL_Renderer *gRenderer) {
	SDL_Rect renderQuad = shape->getRenderQuad();

	if (gTexture != NULL)
		SDL_RenderCopy(gRenderer, gTexture, NULL, &renderQuad);

	for (int  i = 0; i < OBJECT_2D_SIDES; i++) {
		if (boxes[i] == NULL) continue;
		boxes[i]->render(gRenderer);
	}
}


void Graphics::GameObject2D::move() {
	// move main presentation shape
	shape->setX(shape->getX() + velX);
	shape->setY(shape->getY() + velY);

	// now move boxes
	for (int i = 0; i < OBJECT_2D_SIDES; i++) {
		if (boxes[i] == NULL) continue;
		
		boxes[i]->setX(boxes[i]->getX() + velX);
		boxes[i]->setY(boxes[i]->getY() + velY);

	}
}


void Graphics::GameObject2D::move(int x, int y) {
	// move main presentation shape
	shape->setX(shape->getX() + x);
	shape->setY(shape->getY() + y);

	// now move boxes
	for (int i = 0; i < OBJECT_2D_SIDES; i++) {
		if (boxes[i] == NULL) continue;
		
		boxes[i]->setX(boxes[i]->getX() + x);
		boxes[i]->setY(boxes[i]->getY() + y);

	}
}


void Graphics::GameObject2D::setVelX(int velX) {
	this->velX = velX;
}


void Graphics::GameObject2D::setVelY(int velY) {
	this->velY = velY;
}


int Graphics::GameObject2D::getVelX() {
	return velX;
}


int Graphics::GameObject2D::getVelY() {
	return velY;
}


Collisions::BoundBox** Graphics::GameObject2D::getBoxes() {
	return boxes; // valjda ce raditi
}


Geometry::Shape* Graphics::GameObject2D::getShape() {
	return shape;
}


SDL_Texture* Graphics::GameObject2D::getTexture() {
	return gTexture;
}


void Graphics::GameObject2D::setPosition(int x, int y) {
	// now move boxes
	for (int i = 0; i < OBJECT_2D_SIDES; i++) {
		if (boxes[i] == NULL) continue;
		
		boxes[i]->setX(boxes[i]->getX() - shape->getX() + x);
		boxes[i]->setY(boxes[i]->getY() - shape->getY() + y);

	}

	// move main presentation shape
	shape->setX(x);
	shape->setY(y);


}
