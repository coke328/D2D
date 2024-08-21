#include "Shapes.h"


std::array<std::pair<Vector2f*, unsigned int>, 20> Shapes::shapes;

void Shapes::Initialize()
{
	Vector2f* tmp = new Vector2f[4];
	shapes[objectsShape::Box_10x40] = {tmp,4};
	tmp[0] = { 5,20 };	tmp[1] = { -5,20 };	tmp[2] = { -5,-20 }; tmp[3] = { 5,-20 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_10x50] = { tmp,4 };
	tmp[0] = { 5,25 };	tmp[1] = { -5,25 };	tmp[2] = { -5,-25 }; tmp[3] = { 5,-25 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_10x60] = { tmp,4 };
	tmp[0] = { 5,30 };	tmp[1] = { -5,30 };	tmp[2] = { -5,-30 }; tmp[3] = { 5,-30 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_20x20] = { tmp,4 };
	tmp[0] = { 10,10 };	tmp[1] = { -10,10 };	tmp[2] = { -10,-10 }; tmp[3] = { 10,-10 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_20x40] = { tmp,4 };
	tmp[0] = { 10,20 };	tmp[1] = { -10,20 };	tmp[2] = { -10,-20 }; tmp[3] = { 10,-20 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_40x10] = { tmp,4 };
	tmp[0] = { 20,5 };	tmp[1] = { -20,5 };	tmp[2] = { -20,-5 }; tmp[3] = { 20,-5 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_40x20] = { tmp,4 };
	tmp[0] = { 20,10 };	tmp[1] = { -20,10 };	tmp[2] = { -20,-10 }; tmp[3] = { 20,-10 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_40x40] = { tmp,4 };
	tmp[0] = { 20,20 };	tmp[1] = { -20,20 };	tmp[2] = { -20,-20 }; tmp[3] = { 20,-20 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_50x10] = { tmp,4 };
	tmp[0] = { 25,5 };	tmp[1] = { -25,5 };	tmp[2] = { -25,-5 }; tmp[3] = { 25,-5 };

	tmp = new Vector2f[4];
	shapes[objectsShape::Box_60x10] = { tmp,4 };
	tmp[0] = { 30,5 };	tmp[1] = { -30,5 };	tmp[2] = { -30,-5 }; tmp[3] = { 30,-5 };

	tmp = new Vector2f[3];
	shapes[objectsShape::Horn_20x20] = { tmp,3 };
	tmp[0] = { 10,-10 };	tmp[1] = { 0,10 };	tmp[2] = { -10,-10 };

	tmp = new Vector2f[3];
	shapes[objectsShape::Horn_40x40] = { tmp,3 };
	tmp[0] = { 20,-20 };	tmp[1] = { 0,20 };	tmp[2] = { -20,-20 };

	tmp = new Vector2f[3];
	shapes[objectsShape::SlopeRight_20x20] = { tmp,3 };
	tmp[0] = { -6,-6 };	tmp[1] = { 14,-6 };	tmp[2] = { -6,14 };

	tmp = new Vector2f[3];
	shapes[objectsShape::SlopeRight_40x20] = { tmp,3 };
	tmp[0] = { -12,-6 };	tmp[1] = { 28,-6 };	tmp[2] = { -12,14 };

	tmp = new Vector2f[3];
	shapes[objectsShape::SlopeLeft_20x20] = { tmp,3 };
	tmp[0] = { 6,-6 };	tmp[1] = { -14,-6 };	tmp[2] = { 6,14 };

	tmp = new Vector2f[3];
	shapes[objectsShape::SlopeLeft_40x20] = { tmp,3 };
	tmp[0] = { 12,-6 };	tmp[1] = { -28,-6 };	tmp[2] = { 12,14 };

	tmp = new Vector2f[8];
	shapes[objectsShape::Octagon_20x20] = { tmp,8 };
	tmp[0] = { 10,0 };	tmp[1] = { 7,7 };	tmp[2] = { 0,10 }; tmp[3] = {-7,7};
	tmp[4] = { -10,0 };	tmp[5] = { -7,-7 };	tmp[6] = { 0,-10 }; tmp[7] = { 7,-7 };

	tmp = new Vector2f[8];
	shapes[objectsShape::Octagon_40x40] = { tmp,8 };
	tmp[0] = { 20,0 };	tmp[1] = { 14,14 };	tmp[2] = { 0,20 }; tmp[3] = { -14,14 };
	tmp[4] = { -20,0 };	tmp[5] = { -14,-14 };	tmp[6] = { 0,-20 }; tmp[7] = { 14,-14 };

	tmp = new Vector2f[3];
	shapes[objectsShape::Triangle_20] = { tmp,3 };
	tmp[0] = { 10,-6.667 };	tmp[1] = { 0,13.333 };	tmp[2] = { -10,-6.667 };

	tmp = new Vector2f[3];
	shapes[objectsShape::Triangle_40] = { tmp,3 };
	tmp[0] = { 20,-13.334 };	tmp[1] = { 0,26.666 };	tmp[2] = { -20,-13.334 };

}

const std::pair<Vector2f*, unsigned int>& Shapes::GetShape(objectsShape _shape)
{
	return shapes[_shape];
}
