#include "transform.h"

mat4x4 Transform::transform()
{
	mat4x4 myScale = mat4::scale(s);
	mat4x4 myTranslate = mat4::translate(pos);
	mat4x4 myRotate = mat4::rotateXYZ(modelAngle);

	return myTranslate * myRotate * myScale;
}

void Transform::showImGuiControls()
{
	ImGui::SliderFloat3("translate", pos.e, 0, 5);
	ImGui::SliderFloat3("scale", s.e, 0, 5);
	ImGui::SliderFloat3("Rotate", modelAngle.e, 0, 5);
}