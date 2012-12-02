#version 120

smooth in vec3 fragmentColor;
out vec3 newCoords;

void main()
{
	float boundX = 0.0, boundY = 0.0, boundZ = 0.0;
	float tmpX = 0.5, tmpY = 0.5, tmpZ = 0.5;
	float powOfTwo = 0.5;

	int i;

	newCoords = fragmentColor ;

	for(i = 1; i <= 5; ++i)
	{
		if( fragmentColor .x < tmpX && fragmentColor .y < tmpY && fragmentColor .z < tmpZ)
		{
			newCoords = vec3(0.0, 0.0, 0.0);
			break;
		}
		else
		{
			if(fragmentColor .x > tmpX)
			{
				boundX += powOfTwo;
			}
			else if(fragmentColor .y > tmpY)
			{
				boundY += powOfTwo;
			}
			else if(fragmentColor .z > tmpZ)
			{
				boundZ += powOfTwo;
			}
			powOfTwo *= 0.5;
			tmpY = boundY + powOfTwo;
			tmpZ = boundZ + powOfTwo;
			tmpX = boundX + powOfTwo;
		}
	}
}
