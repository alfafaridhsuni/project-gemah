//#version 330
//
//smooth in vec4 objectColor;
//
//out vec4 outputColor;
//
//void main()
//{
//	outputColor = objectColor;
//}
#version 330

smooth in vec4 theColor;

out vec4 outputColor;

void main()
{
    outputColor = vec4(5.5f, 0.5f, 0.5f, 1.0f);
}
