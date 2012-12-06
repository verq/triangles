#version 120

smooth in vec3 fragmentColor;
out vec3 new_vector;

void main() {
	new_vector = fragmentColor;
	float radius = 0.05;
	int i;
	int depth = int(fragmentColor.y / (2.0 * radius));
	float coord_x, coord_z, coord_y;
	coord_y = depth * radius * 2.0 + radius;


	for(int i = 0; i < 16 - depth; i++) {
		coord_x = 1 - (radius + (i + depth) * 2.0 * radius);
		coord_z =  i * 2.0 * radius  + radius;

		if ((fragmentColor.x - coord_x) * (fragmentColor.x - coord_x) + (fragmentColor.y - coord_y) * (fragmentColor.y - coord_y) + 
			(fragmentColor.z - coord_z) * (fragmentColor.z - coord_z) <= radius * radius ) {
			new_vector  = vec3(0.0, 0.0, 0.6);
		} 

	}
} 

