

GLfloat* Draw_Character(char );

GLfloat* Draw_Character(char temp)
{
	static GLfloat texCoords[8];
	GLfloat x1,x2,y1,y2;
	switch(temp)
	{
		case '0':
		{
		x1 = 0.47265625f;
		x2 = 0.505859375f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '1':
		{
		x1 = 0.51171875f;
		x2 = 0.53515625f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '2':
		{
		x1 = 0.541015625f;
		x2 = 0.5703125f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '3':
		{
		x1 = 0.57421875f;
		x2 = 0.603515625f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '4':
		{
		x1 = 0.60546875f;
		x2 = 0.63671875f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '5':
		{
		x1 = 0.640625f;
		x2 = 0.669921875f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '6':
		{
		x1 = 0.671875f;
		x2 = 0.705078125f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '7':
		{
		x1 = 0.70703125f;
		x2 = 0.73828125f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '8':
		{
		x1 = 0.740234375f;
		x2 = 0.76953130f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case '9':
		{
		x1 = 0.7734375f;
		x2 = 0.8046875f;
		y1 = 0.9375f;
		y2 = 0.982421875f;
		}
		break;
		case 'A':
		{
		x1 = 0.083984375f;
		x2 = 0.123046875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'B':
		{
		x1 = 0.125f;
		x2 = 0.158203125f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'C':
		{
		x1 = 0.16015625f;
		x2 = 0.197265625f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'D':
		{
		x1 = 0.19921875f;
		x2 = 0.23828125f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'E':
		{
		x1 = 0.2421875f;
		x2 = 0.2734375f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'F':
		{
		x1 = 0.27734375f;
		x2 = 0.30859375f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'G':
		{
		x1 = 0.30859375f;
		x2 = 0.34765625f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'H':
		{
		x1 = 0.3515625f;
		x2 = 0.388671875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'I':
		{
		x1 = 0.392578125f;
		x2 = 0.4140625f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'J':
		{
		x1 = 0.4140625f;
		x2 = 0.4375f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'K':
		{
		x1 = 0.443359375f;
		x2 = 0.478515625f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'L':
		{
		x1 = 0.48046875f;
		x2 = 0.509765625f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'M':
		{
		x1 = 0.51171875f;
		x2 = 0.5546875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'N':
		{
		x1 = 0.560546875f;
		x2 = 0.595703125f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'O':
		{
		x1 = 0.599609375f;
		x2 = 0.642578125f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'P':
		{
		x1 = 0.646484375f;
		x2 = 0.6796875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'Q':
		{
		x1 = 0.6796875f;
		x2 = 0.72265625f;
		y1 = 0.849609375f;
		y2 = 0.908203125f;
		}
		break;
		case 'R':
		{
		x1 = 0.7265625f;
		x2 = 0.763671875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'S':
		{
		x1 = 0.765625f;
		x2 = 0.796875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'T':
		{
		x1 = 0.80078125f;
		x2 = 0.8359375f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'U':
		{
		x1 = 0.837890625f;
		x2 = 0.873046875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'V':
		{
		x1 = 0.875f;
		x2 = 0.9140625f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'W':
		{
		x1 = 0.916015625f;
		x2 = 0.96875f;
		y1 = 0.861328125f;
		y2 = 0.908203125f;
		}
		break;
		case 'X':
		{
		x1 = 0.0f;
		x2 = 0.03515625f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'Y':
		{
		x1 = 0.0390625f;
		x2 = 0.072265625f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'Z':
		{
		x1 = 0.07421875f;
		x2 = 0.10546875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'a':
		{
		x1 = 0.2890625f;
		x2 = 0.3203125f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'b':
		{
		x1 = 0.32421875f;
		x2 = 0.35546875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'c':
		{
		x1 = 0.357421875f;
		x2 = 0.38671875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'd':
		{
		x1 = 0.38671875f;
		x2 = 0.419921875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'e':
		{
		x1 = 0.423828125f;
		x2 = 0.451171875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'f':
		{
		x1 = 0.455078125f;
		x2 = 0.474609375f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'g':
		{
		x1 = 0.478515625f;
		x2 = 0.5078125f;
		y1 = 0.7734375f;
		y2 = 0.83203125f;
		}
		break;
		case 'h':
		{
		x1 = 0.51171875f;
		x2 = 0.54296875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'i':
		{
		x1 = 0.544921875f;
		x2 = 0.556640625f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'j':
		{
		x1 = 0.55859375f;
		x2 = 0.57421875f;
		y1 = 0.7734375f;
		y2 = 0.83203125f;
		}
		break;
		case 'k':
		{
		x1 = 0.578125f;
		x2 = 0.609375f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'l':
		{
		x1 = 0.609375f;
		x2 = 0.619140625f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'm':
		{
		x1 = 0.623046875f;
		x2 = 0.671875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'n':
		{
		x1 = 0.67578125f;
		x2 = 0.70703125f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'o':
		{
		x1 = 0.70703125f;
		x2 = 0.7421875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'p':
		{
		x1 = 0.744140625f;
		x2 = 0.775390625f;
		y1 = 0.7734375f;
		y2 = 0.83203125f;
		}
		break;
		case 'q':
		{
		x1 = 0.77734375f;
		x2 = 0.810546875f;
		y1 = 0.7734375f;
		y2 = 0.83203125f;
		}
		break;
		case 'r':
		{
		x1 = 0.814453125f;
		x2 = 0.8359375f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 's':
		{
		x1 = 0.8359375f;
		x2 = 0.861328125f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 't':
		{
		x1 = 0.86328125f;
		x2 = 0.884765625f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'u':
		{
		x1 = 0.88671875f;
		x2 = 0.91796875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'v':
		{
		x1 = 0.91796875f;
		x2 = 0.951171875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'w':
		{
		x1 = 0.953125f;
		x2 = 0.998046875f;
		y1 = 0.78515625f;
		y2 = 0.83203125f;
		}
		break;
		case 'x':
		{
		x1 = 0.0f;
		x2 = 0.03125f;
		y1 = 0.708984375f;
		y2 = 0.7578125f;
		}
		break;
		case 'y':
		{
		x1 = 0.03125f;
		x2 = 0.0625f;
		y1 = 0.697265625f;
		y2 = 0.7578125f;
		}
		break;
		case 'z':
		{
		x1 = 0.064453125f;
		x2 = 0.08984375f;
		y1 = 0.708984375f;
		y2 = 0.7578125f;
		}
		break;
	default :
		{
		x1 = 0.0f;
		x2 = 1.0f;
		y1 = 0.0f;
		y2 = 1.0f;
		}
		break;
	}

texCoords[0] = x1;
texCoords[1] = y1;
texCoords[2] = x2;
texCoords[3] = y1;
texCoords[4] = x1;
texCoords[5] = y2;
texCoords[6] = x2;
texCoords[7] = y2;

return texCoords; 
}