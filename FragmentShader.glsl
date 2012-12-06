#version 120

smooth in vec3 fragmentColor;
out vec3 new_vector;

void main() {
	float factor = 0.5;
	float bound_x = 0.0, bound_y = 0.0, bound_z = 0.0;
	float coord_x = factor, coord_y = factor, coord_z = factor;
	float power = factor;

	new_vector = fragmentColor;

	for(int i = 0; i < 6; i++) {
		if (fragmentColor.x < coord_x && fragmentColor.y < coord_y  && fragmentColor.z < coord_z) {
			new_vector = vec3(0.0, 0.0, 0.0);
		} else {
			if (fragmentColor.x > coord_x) bound_x = bound_x + power;
			else if (fragmentColor.y > coord_y) bound_y = bound_y + power;
			else if (fragmentColor.z > coord_z)  bound_z = bound_z + power;
			
			power = power * factor;
			coord_x =  bound_x + power;
			coord_y =  bound_y + power;
			coord_z =  bound_z + power;
		}
	}
}
