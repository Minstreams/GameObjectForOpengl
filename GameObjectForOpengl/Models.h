#pragma once
class Models {
private:
	static Models* list;
public:
	static Models* List() {
		if (list == NULL) {
			list = new Models();
		}
		return list;
	}
	//以下是表列
	const Model model1 = Model("data/Models/nanosuit/nanosuit.obj");
	const Model model2 = Model("data/Models/mazda 3/mazda 3.obj");
	const Model earth = Model("data/Models/earth/earth.obj");
};

Models* Models::list = NULL;