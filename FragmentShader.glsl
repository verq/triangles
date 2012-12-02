#version 120

smooth in vec3 fragmentColor;
out vec3 newCoords;

void main()
{
	float sth = 0.5;
	float bound_x = 0.0, bound_y = 0.0, bound_z = 0.0;
	float coord_x =  sth, coord_y =  sth, coord_z =  sth;
	float power =  sth;

	newCoords = fragmentColor;

	for(int i = 0; i <= 3; i++) {
		if (fragmentColor.x < coord_x && fragmentColor.y < coord_y  && fragmentColor.z < coord_z) {
			newCoords = vec3(0.0, 0.0, 0.0);
			
		} else {
			if (fragmentColor.x > coord_x) bound_x += power;
			else if (fragmentColor.y > coord_y) bound_y += power;
			else if (fragmentColor .z > coord_z)  bound_z += power;
			
			power *= sth;
			coord_x =  bound_x + power;
			coord_y =  bound_y + power;
			coord_z =  bound_z + power;
		}
	}
}
