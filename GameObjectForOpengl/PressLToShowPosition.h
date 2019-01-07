#pragma once
class PressLToShowPosition : public MonoBehaviour {
public:
	void Update()override {
		if (Input::GetKey('l')) {
			Vector3 out;
			out = transform->GetPosition();
			printf_s("\nPosition:%.3f,%.3f,%.3f  %s", out.x, out.y, out.z, gameObject->Name);
		}
	}

};
